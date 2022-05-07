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

	/**
	* @brief consctructor
	*  @details it'll build the settings for our analyzer , set up  each signal on one channel
	*  @param  mALEChannel  Address latch enable: Loads an address from I/O[7:0] into the address register
	*  @param mCEChannel Chip enable: Enables or disables one or more die (LUNs) in a target.
	*  @param mCLEChannel Command latch enable: Loads a command from I/O[7:0] into the command register.
	*  @param mREChannel Read enable: Transfers serial data from the NAND Flash to the host system.
	*  @param mWEChannel Write enable: Transfers commands, addresses, and serial data from the host system to the NAND Flash.
	*
	*	 @param mDQSChannel ...
	*  @param mDQChannel[0:7] Data inputs/outputs: The bidirectional I/Os transfer address, data, and command infor-
	mation.
	*  @param mRBChannel Ready/busy: An open-drain, active-low output that requires an external pull-up resistor.
	This signal indicates target array activity.
	*
	*********************************/
	ONFIAnalyzerSettings();
	/**
	*  @brief Destructor
	* @details Destructor of the class ONFIAnalyzerSettings
	*************************/
	virtual ~ONFIAnalyzerSettings();
	/**
	* 	@brief SetSettingsFromInterfaces
	*  @details This function will copy the values saved in our interface objects to
	*  our settings variables
	**********************/
	virtual bool SetSettingsFromInterfaces();
	/**
	* @brief  UpdateInterfacesFromSettings
	* @details This function will copy the values saved in our interface ojbects to
	*  our settings variables
	**********************/
	void UpdateInterfacesFromSettings();
	/**
	* @brief   LoadSettings
	* @details This function will  serialize all variables set upped
	*	******/
	virtual void LoadSettings( const char* settings );
	/**
	* @brief SaveSettings
	* @details This function will save all of our settings variables into a single string
	*****/
	virtual const char* SaveSettings();


	/// @details  the channel CE
	Channel mCEChannel;
	/// @details  the channel ALE
	Channel mALEChannel;
<<<<<<< HEAD

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
=======
		/// @details  the channel CE
	Channel mCEChannel;
		/// @details  the channel CLE
	Channel mCLEChannel;
		/// @details  the channel RE
	Channel mREChannel;
		/// @details  the channel WE
	Channel mWEChannel;
		/// @details  the channel R/B
	Channel mRBChannel;

	Channel mDQSChannel;
	/// @details  the channel DQS
	Channel mDQChannel;
	/// @details  the channel I/O[1]
	Channel mDQ_1Channel;
	/// @details  the channel I/O[2]
	Channel mDQ_2Channel;
	/// @details  the channel I/O[3]
	Channel mDQ_3Channel;
	/// @details  the channel I/O[4]
	Channel mDQ_4Channel;
	/// @details  the channel I/O[5]
	Channel mDQ_5Channel;
	/// @details  the channel I/O[6]
	Channel mDQ_6Channel;
		/// @details  the channel I/O[7]
	Channel mDQ_7Channel;

>>>>>>> version_1

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
<<<<<<< HEAD

std::auto_ptr< AnalyzerSettingInterfaceChannel >  mDQSChannelInterface;
=======
	/// @details the interface for the channel R/B
std::auto_ptr< AnalyzerSettingInterfaceChannel > mRBChannelInterface;
/// @details the interface for the channel DQS
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQSChannelInterface;
/// @details the interface for the channel I/O[0]
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQChannelInterface;
/// @details the interface for the channel I/O[1]
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_1ChannelInterface;
/// @details the interface for the channel I/O[2]
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_2ChannelInterface;
/// @details the interface for the channel I/O[3]
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_3ChannelInterface;
/// @details the interface for the channel I/O[4]
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_4ChannelInterface;
/// @details the interface for the channel I/O[5]
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_5ChannelInterface;
/// @details the interface for the channel I/O[6]
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_6ChannelInterface;
/// @details the interface for the channel I/O[7]
std::auto_ptr< AnalyzerSettingInterfaceChannel > mDQ_7ChannelInterface;


>>>>>>> version_1

};

#endif //ONFI_ANALYZER_SETTINGS
