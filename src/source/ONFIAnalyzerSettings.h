#ifndef ONFI_ANALYZER_SETTINGS
#define ONFI_ANALYZER_SETTINGS

#include "../AnalyzerSDK/include/AnalyzerSettings.h"
#include "../AnalyzerSDK/include/AnalyzerTypes.h"


/**
 *  @file   ONFIAnalyzerSettings.h
 *  @brief  this fucntion will define the settings our analyzer needs,
 *	and create interfaces that’ll allow the Logic software to display a GUI for the settings.
 *     we'll also implement serialization for these settings so they can be saved and recalled from disk.
 *
 *
 ***********************************************/

class ONFIAnalyzerSettings : public AnalyzerSettings
{

public:
	ONFIAnalyzerSettings();
	virtual ~ONFIAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LodSettings( const char* settings );
	virtual const char* SaveSettings();


	Channel mInputChannel;
	U32 mBitRate;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mBitRateInterface;
};

#endif //ONFI_ANALYZER_SETTINGS
