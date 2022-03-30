#include "ONFISimulationDataGenerator.h"
#include "ONFIAnalyzerSettings.h"

#include <AnalyzerHelpers.h>

/**
* @brief Consctructor
*  @details ...
***/
ONFISimulationDataGenerator::ONFISimulationDataGenerator()
:	mALEText( "My first analyzer, woo hoo!" ),
mStringIndex( 0 )
{
}
/**
* @brief Destructor
*  @details ...
***/
ONFISimulationDataGenerator::~ONFISimulationDataGenerator()
{
}

/**
*  @brief This function provides  the state of things
* as they are going to be when we start simulating.
* on our channel
**/
void ONFISimulationDataGenerator::Initialize( U32 simulation_sample_rate,
	ONFIAnalyzerSettings* settings )
	{
		mSimulationSampleRateHz = simulation_sample_rate;
		mSettings = settings;

		/*
		*  not look at before done
		*/
		if( settings->mALEChannel != UNDEFINED_CHANNEL )
		mALESimulationData = onfiSimulationChannels.Add( settings->mALEChannel, mSimulationSampleRateHz, BIT_HIGH );
		else
		mALESimulationData = NULL;

	}

	/**
	* @brief this function is repeatedly called to request mores simulated data
	*****/
	U32 ONFISimulationDataGenerator::GenerateSimulationData( U64 largest_sample_requested,
		U32 sample_rate,
		SimulationChannelDescriptor** simulation_channel )
		{
			U64 adjusted_largest_sample_requested = AnalyzerHelpers::AdjustSimulationTargetSample( largest_sample_requested, sample_rate, mSimulationSampleRateHz );

			// looak at doc to add new generate data
			/*	while( mALESimulationData.GetCurrentSampleNumber() < adjusted_largest_sample_requested )
			{
			CreateALEByte();
		}*/
		*simulation_channel = onfiSimulationChannels.GetArray();
		return onfiSimulationChannels.GetCount();
	}



	void ONFISimulationDataGenerator::CreateALEByte()
	{
		U32 samples_per_bit = mSimulationSampleRateHz ;

		U8 byte = mALEText[ mStringIndex ];
		mStringIndex++;
		/*if( mStringIndex == mALEText.size() )
		mStringIndex = 0;

		//we're currenty high
		//let's move forward a little
		mALESimulationData.Advance( samples_per_bit * 10 );

		mALESimulationData.Transition();  //low-going edge for start bit
		mALESimulationData.Advance( samples_per_bit );  //add start bit time

		U8 mask = 0x1 << 7;
		for( U32 i=0; i<8; i++ )
		{
		if( ( byte & mask ) != 0 )
		mALESimulationData.TransitionIfNeeded( BIT_HIGH );
		else
		mALESimulationData.TransitionIfNeeded( BIT_LOW );

		mALESimulationData.Advance( samples_per_bit );
		mask = mask >> 1;
	}

	mALESimulationData.TransitionIfNeeded( BIT_HIGH ); //we need to end high

	//lets pad the end a bit for the stop bit:
	mALESimulationData.Advance( samples_per_bit );*/
}
