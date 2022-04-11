#ifndef ONFI_ANALYZER_H
#define ONFI_ANALYZER_H

#include <Analyzer.h>
#include "ONFIAnalyzerResults.h"
#include "ONFISimulationDataGenerator.h"

/**
* @file ONFIAnalyzer.h
* @breif  TClass analyzer this in this class we going to analyze
*  each signal of data dump according to ONFI protocol
***/
class ONFIAnalyzerSettings;
class ANALYZER_EXPORT ONFIAnalyzer : public Analyzer2
{
public:
	/**
	* @details we use this enum type to store data
	* from signal according to their naturel ,
	* for example if it's a cmd data the enum will have the value kcommand
	*****/
	enum FrameType
			{
				/// none value
				kInvalid,
				/// this is a fake value
				kEnvelope,
				/// the value of command
				kCommand,
				/// the value of address from signal
				kAddress,
				/// the value of data from signal
				kData,
			};
	/**
	*  @brief Constructor
	*  @details
	*
	*********************************/
	ONFIAnalyzer();
	/**
	*  @brief Destructor
	*  @details
	*
	*********************************/
	virtual ~ONFIAnalyzer();
	/**
		*  @brief SetupResults
		*  @details this function set up the channel that will show up
		* the resulat of our Analyzer on Saleae's software
		*********************************/
	virtual void SetupResults();
	/**
	*  @brief WorkerThread
	*  @details this function is the heart of our Analyzer, here we analyze the onfi protocol
	*******************/
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	/**
	*  @brief GetMinimumSampleRateHz
	*  @details This function check if the  selected sample rate is sufficient
	*		to get good results for the analyzer.
	**************/
	virtual U32 GetMinimumSampleRateHz();
	/**
		* @brief GetAnalyzerName
		* @details return the Analyzer's name
		**************/
	virtual const char* GetAnalyzerName() const;
	/**
	*  @brief NeedsRerun
	*	@details this function is called when the analyzer has finished
	*  @return true for run over again the same data or false to not
	**/
	virtual bool NeedsRerun();

	U8 SyncAndReadDQ(U64 sample_number);
	bool AddFrame(FrameType frame_type,
										U64 start,
										U64 end = 0,
										U64 data1 = 0,
										U64 data2 = 0,
										U8 flags = 0
									);

									/**
										@brief analyzerNVDDRxx
										@details	pseudocode of our analyze of onfi protocol :
										@code
									  while True:
									    get the bit of CE signal
											if the current bit od CE is equal to 1 then :
											 				we move on to the next bit
											else then:
													get the bit of R/E signal and move it where CE signal is 0
													if the bit of R/E is equal to 1 the :
													      get the signals of ALE ,CLE and WE and mowe all where R/E is equal to 1
																if ALE signal is equal to 1 then :
																     the Nand  interface is sending a addres cycle
																if CLE signal is equal to 1 then :
																      the Nand  interface is sending a command cycle
																if CLE and ALE signals  are equals to 0  and WE is equal to 1 then :
																        the Nand  interface is reading  a DATA input cycle
												  else then :
													      if CLE and ALE are equals to 0 and WE is equal to 1 the :
																					the Nand  interface is reading a DATA output cycle
										@endcode
										****/
										void analyzerNVDDRxx();

protected: //vars
	std::auto_ptr< ONFIAnalyzerSettings > mSettings;
	std::auto_ptr< ONFIAnalyzerResults > mResults;


	/// @details  the address latch enable signal
		AnalyzerChannelData* aleChannel;
		/// @details  the chip enable signal
		AnalyzerChannelData* ceChannel;
		/// @details  the commmand latch enable signal
		AnalyzerChannelData* cleChannel;
		/// @details  the read enable signal
		AnalyzerChannelData* reChannel;
		/// @details  the write enable signal
		AnalyzerChannelData* weChannel;
		/// @details  the he strobe signal which indicate when the data should be latched
		AnalyzerChannelData* dqsChannel;
		/// @details  the read/busy signal
		AnalyzerChannelData* rbChannel;
		/// @details  the Data Bus Inversion signal
		std::array<AnalyzerChannelData*,8> dqChannel={};

};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //ONFI_ANALYZER_H
