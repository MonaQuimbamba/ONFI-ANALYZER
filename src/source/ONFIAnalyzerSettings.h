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


	Channel mALEChannel;
	Channel mCEChannel;
	Channel mCLEChannel;
	Channel mLOCKChannel;
	Channel mREChannel;
	Channel mWEChannel;
	Channel mWPChannel;
	Channel mIOChannel;
	Channel mRBChannel;

	U32 mBitRate;

protected:

	std::auto_ptr< AnalyzerSettingInterfaceChannel > mALEChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel > mCEChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel > mCLEChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel > mLOCKChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel > mREChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel >  mWEChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel > mWPChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel > mIOChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel > mRBChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mBitRateInterface;
};

#endif //ONFI_ANALYZER_SETTINGS
