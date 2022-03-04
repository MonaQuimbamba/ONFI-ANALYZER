#include "ONFIAnalyzer.h"
#include "ONFIAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

ONFIAnalyzer::ONFIAnalyzer()
:	Analyzer2(),
	mSettings( new ONFIAnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
}

ONFIAnalyzer::~ONFIAnalyzer()
{
	KillThread();
}

void ONFIAnalyzer::SetupResults()
{
	mResults.reset( new ONFIAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mALEChannel );
}

void ONFIAnalyzer::WorkerThread()
{
	mSampleRateHz = GetSampleRate();

	mALEChannel = GetAnalyzerChannelData( mSettings->mALEChannel );

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

bool ONFIAnalyzer::NeedsRerun()
{
	return false;
}

U32 ONFIAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 ONFIAnalyzer::GetMinimumSampleRateHz()
{
	return 67 * 4;
}

const char* ONFIAnalyzer::GetAnalyzerName() const
{
	return "ONFI Protocol";
}

const char* GetAnalyzerName()
{
	return "ONFI Protocol";
}

Analyzer* CreateAnalyzer()
{
	return new ONFIAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}
