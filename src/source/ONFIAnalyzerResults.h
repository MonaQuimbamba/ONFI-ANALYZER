#ifndef ONFI_ANALYZER_RESULTS
#define ONFI_ANALYZER_RESULTS

#include <AnalyzerResults.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

/**
* @file ONFIAnalyzerResults.h
* @brief This class translates saved results into hex string value for a
*  variety of uses. Here we'll start thinking about the format that our results will be saved in.
*
************************/
class ONFIAnalyzer;
class ONFIAnalyzerSettings;


class ONFIAnalyzerResults : public AnalyzerResults
{
public:
	/**
	*  @brief Constructor
	*  @details Constructor of the class ONFIAnalyzerResults
	*
	*********************************/
	ONFIAnalyzerResults( ONFIAnalyzer* analyzer, ONFIAnalyzerSettings* settings );
	/**
	*  @brief Destructor
	*  @details Destructor of the class ONFIAnalyzerResults
	*
	*********************************/
	virtual ~ONFIAnalyzerResults();
	/**
	*  @brief GenerateBubbleText
	*  @details This function will show up the  interpretation  of signals
	*
	*********************************/
	virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
	/**
	*  @brief GenerateExportFile
	*  @details This function will show up the  interpretation  of signals
	*
	*********************************/
	virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );
	virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base );
	virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
	virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );


protected: //functions

protected:  //vars
	ONFIAnalyzerSettings* mSettings;
	ONFIAnalyzer* mAnalyzer;
};

#endif //ONFI_ANALYZER_RESULTS
