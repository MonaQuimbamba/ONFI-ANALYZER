#ifndef ONFI_ANALYZER_H
#define ONFI_ANALYZER_H

#include <Analyzer.h>
#include "ONFIAnalyzerResults.h"
#include "ONFISimulationDataGenerator.h"



/**
* @file ONFIAnalyzer.h
* @breif  The main thing you’ll do here
* is translate data streams into results, based on our protocol.
***/

class ONFIAnalyzerSettings;
class ANALYZER_EXPORT ONFIAnalyzer : public Analyzer2
{
public:
	enum FrameType
	{
		kInvalid,
		kEnvelope,
		kCommand,
		kAddress,
		kData,
	};

	ONFIAnalyzer();
	virtual ~ONFIAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

	U8 SyncAndReadDQ(U64 sample_number);
	bool AddFrame(FrameType frame_type,
		U64 start,
		U64 end = 0,
		U64 data1 = 0,
		U64 data2 = 0,
		U8 flags = 0
	);


	protected: //vars
	std::auto_ptr< ONFIAnalyzerSettings > mSettings;
	std::auto_ptr< ONFIAnalyzerResults > mResults;
	ONFISimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;


	// raw pointer for each input
	AnalyzerChannelData* mALEChannel;
	AnalyzerChannelData* mCEChannel;
	AnalyzerChannelData* mCLEChannel;
	AnalyzerChannelData* mREChannel;
	AnalyzerChannelData* mWEChannel;
	AnalyzerChannelData* mDQSChannel;


	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //ONFI_ANALYZER_H
