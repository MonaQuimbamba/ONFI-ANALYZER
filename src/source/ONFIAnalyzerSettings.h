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
		/// @details  the channel LOCK
	Channel mREChannel;
		/// @details  the channel RE
	Channel mWEChannel;

		/// @details  the channel R/B
	Channel mRBChannel;

	Channel mDQSChannel;
	/// @details  the channel I/O
	Channel mDQChannel;

	Channel mDQ_1Channel;
	Channel mDQ_2Channel;
	Channel mDQ_3Channel;
	Channel mDQ_4Channel;
	Channel mDQ_5Channel;
	Channel mDQ_6Channel;
	Channel mDQ_7Channel;


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


	/// @details the interface for the channel R/B
std::auto_ptr< AnalyzerSettingInterfaceChannel > mRBChannelInterface;

std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQSChannelInterface;


/// @details the interface for the channel I/O
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQChannelInterface;
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_1ChannelInterface;
/// @details the interface for the channel WP
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_2ChannelInterface;
/// @details the interface for the channel WP
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_3ChannelInterface;
/// @details the interface for the channel WP
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_4ChannelInterface;
/// @details the interface for the channel WP
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_5ChannelInterface;
/// @details the interface for the channel WP
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_6ChannelInterface;
/// @details the interface for the channel WP
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_7ChannelInterface;



};

#endif //ONFI_ANALYZER_SETTINGS
