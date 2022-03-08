#ifndef ONFI_SIMULATION_DATA_GENERATOR
#define ONFI_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>

/**
 *  @file   ONFISimulationDataGenerator.h
 *  @brief  this class will generate simulated data that can be
 *  later to test the analyzer, or provide an example of what your analyzer expects
 *
 *
 ***********************************************/

class ONFIAnalyzerSettings;

class ONFISimulationDataGenerator
{

public:
	ONFISimulationDataGenerator();
	~ONFISimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, ONFIAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	ONFIAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateALEByte();
	std::string mALEText;
	U32 mStringIndex;

	/*
	* for each channel
	**/
	SimulationChannelDescriptorGroup onfiSimulationChannels;
	SimulationChannelDescriptor* mALESimulationData;

};
#endif //ONFI_SIMULATION_DATA_GENERATOR
