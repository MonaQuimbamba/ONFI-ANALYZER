#include "ONFIAnalyzer.h"
#include "ONFIAnalyzerSettings.h"
#include <AnalyzerChannelData.h>


/**
*  @brief Constructor
*  @details
*
*********************************/
ONFIAnalyzer::ONFIAnalyzer()
:	Analyzer2(),
	mSettings( new ONFIAnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
}


/**
*  @brief Destructor
*  @details
*
*********************************/
ONFIAnalyzer::~ONFIAnalyzer()
{
	KillThread();
}
/**
*  @brief SetupResults
*  @details set up the settings of ou Analyzer
*
*********************************/
void ONFIAnalyzer::SetupResults()
{
	mResults.reset( new ONFIAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	if( mSettings->mALEChannel != UNDEFINED_CHANNEL )
		mResults->AddChannelBubblesWillAppearOn( mSettings->mALEChannel );
	if( mSettings->mCEChannel != UNDEFINED_CHANNEL )
		mResults->AddChannelBubblesWillAppearOn( mSettings->mCEChannel );
}

/**
*  @brief WorkerThread
*  @ details the heart of our Analyzer ...
*******************/

//AnalyzerChannelData give the data from a particular input 
void ONFIAnalyzer::WorkerThread()
{
				mSampleRateHz = GetSampleRate();

				mALEChannel = GetAnalyzerChannelData( mSettings->mALEChannel );
				//mCEChannel = GetAnalyzerChannelData( mSettings->mCEChannel );

				if( mALEChannel->GetBitState() == BIT_LOW )
					mALEChannel->AdvanceToNextEdge();

				U32 samples_per_bit = mSampleRateHz ;
				U32 samples_to_first_center_of_first_data_bit = U32( 1.5 * double( mSampleRateHz )) ;

				for( ; ; )
				{
					U8 data = 0;
					U8 mask = 1 << 7;

					mALEChannel->AdvanceToNextEdge(); //falling edge -- beginning of the start bit

					U64 starting_sample = mALEChannel->GetSampleNumber();

					mALEChannel->Advance( samples_to_first_center_of_first_data_bit );

					for( U32 i=0; i<8; i++ )
					{
						//let's put a dot exactly where we sample this bit:
						mResults->AddMarker( mALEChannel->GetSampleNumber(), AnalyzerResults::Dot, mSettings->mALEChannel );

						if( mALEChannel->GetBitState() == BIT_HIGH )
							data |= mask;

						mALEChannel->Advance( samples_per_bit );

						mask = mask >> 1;
					}


					//we have a byte to save.
					Frame frame;
					frame.mData1 = data;
					frame.mFlags = 0;
					frame.mStartingSampleInclusive = starting_sample;
					frame.mEndingSampleInclusive = mALEChannel->GetSampleNumber();

					mResults->AddFrame( frame );
					mResults->CommitResults();
					ReportProgress( frame.mEndingSampleInclusive );
				}
}

/**
*  @brief NeedsRerun
*	@details this function is called when the analyzer has finished
*  @return true for run over again the same data or false to not
**/
bool ONFIAnalyzer::NeedsRerun()
{
	return false;
}

/**
*  @brief GenerateSimulationData
*  @details function called to get simulated data
****/
U32 ONFIAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

/**
*  @brief GetMinimumSampleRateHz
*  @details This function check if the  selected sample rate is sufficient
*		to get good results for the analyzer.
**************/
U32 ONFIAnalyzer::GetMinimumSampleRateHz()
{
	return 67 * 4;
}

/**
* @brief GetAnalyzerName
* @details return the Analyzer' name
**************/
const char* ONFIAnalyzer::GetAnalyzerName() const
{
	return "ONFI Protocol";
}

/**
* @brief GetAnalyzerName
* @details return the Analyzer' name
**************/

const char* GetAnalyzerName()
{
	return "ONFI Protocol";
}

/**
* @brief CreateAnalyzer
* @details
**************/
Analyzer* CreateAnalyzer()
{
	return new ONFIAnalyzer();
}

/**
* @brief DestroyAnalyzer
* @details this function Simply call delete on the provided pointer.
**************/

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}
