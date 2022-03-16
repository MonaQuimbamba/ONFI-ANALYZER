#ifndef ONFI_ANALYZER_SETTINGS
#define ONFI_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>


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
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();


	/// @details  the channel CE
	Channel mCEChannel;
	/// @details  the channel ALE
	Channel mALEChannel;

		/// @details  the channel CLE
	Channel mCLEChannel;
		/// @details  the channel LOCK
	Channel mREChannel;
		/// @details  the channel WE
	Channel mWEChannel;
	/// @details  the channel DQS
	Channel mDQSChannel;
	/// @details  the channel DQ
	//Channel mDQChannel;

protected:
	/// @details the interface for the channel ALE
std::auto_ptr< AnalyzerSettingInterfaceChannel > mALEChannelInterface;
	/// @details the interface for the channel CE
std::auto_ptr< AnalyzerSettingInterfaceChannel > mCEChannelInterface;
	/// @details the interface for the channel CLE
std::auto_ptr< AnalyzerSettingInterfaceChannel > mCLEChannelInterface;
	/// @details the interface for the channel RE
std::auto_ptr< AnalyzerSettingInterfaceChannel > mREChannelInterface;
	/// @details the interface for the channel WE
std::auto_ptr< AnalyzerSettingInterfaceChannel >  mWEChannelInterface;

std::auto_ptr< AnalyzerSettingInterfaceChannel >  mDQSChannelInterface;

};

#endif //ONFI_ANALYZER_SETTINGS
