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

	/// @details  the channel ALE
	Channel mALEChannel;
		/// @details  the channel CE
	Channel mCEChannel;
		/// @details  the channel CE
	Channel mCLEChannel;
		/// @details  the channel CLE
	Channel mLOCKChannel;
		/// @details  the channel LOCK
	Channel mREChannel;
		/// @details  the channel RE
	Channel mWEChannel;
		/// @details  the channel WP
	Channel mWPChannel;
		/// @details  the channel I/O
	Channel mIOChannel;
		/// @details  the channel R/B
	Channel mRBChannel;

	Channel mDQSChannel;

protected:
	/// @details the interface for the channel ALE
std::auto_ptr< AnalyzerSettingInterfaceChannel > mALEChannelInterface;
	/// @details the interface for the channel CE
std::auto_ptr< AnalyzerSettingInterfaceChannel > mCEChannelInterface;
	/// @details the interface for the channel CLE
std::auto_ptr< AnalyzerSettingInterfaceChannel > mCLEChannelInterface;
	/// @details the interface for the channel LOCK
std::auto_ptr< AnalyzerSettingInterfaceChannel > mLOCKChannelInterface;
	/// @details the interface for the channel RE
std::auto_ptr< AnalyzerSettingInterfaceChannel > mREChannelInterface;
	/// @details the interface for the channel WE
std::auto_ptr< AnalyzerSettingInterfaceChannel >  mWEChannelInterface;
	/// @details the interface for the channel WP
std::auto_ptr< AnalyzerSettingInterfaceChannel > mWPChannelInterface;
	/// @details the interface for the channel I/O
std::auto_ptr< AnalyzerSettingInterfaceChannel > mIOChannelInterface;
	/// @details the interface for the channel R/B
std::auto_ptr< AnalyzerSettingInterfaceChannel > mRBChannelInterface;

std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQSChannelInterface;
};

#endif //ONFI_ANALYZER_SETTINGS
