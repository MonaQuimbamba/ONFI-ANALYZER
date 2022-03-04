#include "ONFIAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


/**
* @brief consctructor
*  @details it'll build the settings for our analyzer , set up  each signal on one channel
*  @param   mALEChannel  Address latch enable: Loads an address from I/O[7:0] into the address register
*  @param mCEChannel Chip enable: Enables or disables one or more die (LUNs) in a target.
*  @param mCLEChannel Command latch enable: Loads a command from I/O[7:0] into the command register.
*  @param mLOCKChannel When LOCK is HIGH during power-up, the BLOCK LOCK function is enabled. To disable the
	BLOCK LOCK, connect LOCK to VSS during power-up, or leave it disconnected (internal
	pull-down).
*
*  @param mREChannel Read enable: Transfers serial data from the NAND Flash to the host system.
*  @param mWEChannel Write enable: Transfers commands, addresses, and serial data from the host system to the NAND Flash.
*
*  @param mWPChannel Write protect: Enables or disables array PROGRAM and ERASE operations
*  @param mIOChannel Data inputs/outputs: The bidirectional I/Os transfer address, data, and command infor-
mation.
*  @param mRBChannel Ready/busy: An open-drain, active-low output that requires an external pull-up resistor.
This signal indicates target array activity.
*  @param  mBitRate
*********************************/


ONFIAnalyzerSettings::ONFIAnalyzerSettings()
:	 mALEChannel( UNDEFINED_CHANNEL ),
	mCEChannel( UNDEFINED_CHANNEL ),
	mCLEChannel( UNDEFINED_CHANNEL ),
	mLOCKChannel( UNDEFINED_CHANNEL ),
	mREChannel( UNDEFINED_CHANNEL ),
	mWEChannel( UNDEFINED_CHANNEL ),
	mWPChannel( UNDEFINED_CHANNEL ),
	mIOChannel( UNDEFINED_CHANNEL ),
	mRBChannel( UNDEFINED_CHANNEL )
{
    /// @details Setting up each AnalyzerSettingInterface object
		// for the moment only AnalyzerSettingInterfaceChannel
		mALEChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mALEChannelInterface->SetTitleAndTooltip( "ALE", "INPUT , Address latch enable" );
		mALEChannelInterface->SetChannel( mALEChannel );
		mALEChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mCEChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mCEChannelInterface->SetTitleAndTooltip( "CE", "INPUT , Chip enable" );
		mCEChannelInterface->SetChannel( mCEChannel );
		mCEChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mCLEChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mCLEChannelInterface->SetTitleAndTooltip( "CLE", "INPUT, Command latch enable" );
		mCLEChannelInterface->SetChannel( mCLEChannel );
		mCLEChannelInterface->SetSelectionOfNoneIsAllowed( true );


		mLOCKChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mLOCKChannelInterface->SetTitleAndTooltip( "LOCK", "INPUT, " );
		mLOCKChannelInterface->SetChannel( mLOCKChannel );
		mLOCKChannelInterface->SetSelectionOfNoneIsAllowed( true );


		mREChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mREChannelInterface->SetTitleAndTooltip( "RE", "INPUT, READ enable" );
		mREChannelInterface->SetChannel( mREChannel );
		mREChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mWEChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mWEChannelInterface->SetTitleAndTooltip( "WE", "INPUT, Write enable " );
		mWEChannelInterface->SetChannel( mWEChannel );
		mWEChannelInterface->SetSelectionOfNoneIsAllowed( true );


		mWPChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mWPChannelInterface->SetTitleAndTooltip( "WP", "INPUT, Write protect" );
		mWPChannelInterface->SetChannel( mWPChannel );
		mWPChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mIOChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mIOChannelInterface->SetTitleAndTooltip( "IO", "I/O, Data inputs/outputs" );
		mIOChannelInterface->SetChannel( mIOChannel );
		mIOChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mRBChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mRBChannelInterface->SetTitleAndTooltip( "RB", "OUTPUT, Ready/busy" );
		mRBChannelInterface->SetChannel( mRBChannel );
		mRBChannelInterface->SetSelectionOfNoneIsAllowed( true );




		AddInterface( mALEChannelInterface.get() );
		AddInterface( mCEChannelInterface.get() );
		AddInterface( mCLEChannelInterface.get() );
		AddInterface( mLOCKChannelInterface.get() );
		AddInterface( mREChannelInterface.get() );
		AddInterface( mWEChannelInterface.get() );
		AddInterface( mWPChannelInterface.get() );
		AddInterface( mIOChannelInterface.get() );
		AddInterface( mRBChannelInterface.get() );




/// @details Specifying the export options
	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

/// @details Specifying which channels are in use
/*
* The analyzer must indicate which channel(s) it is using.
* This is done with the AddChannel function.
 Every time the channel changes (such as when the user changes the channel) the reported channel must be updated. To clear any previous channels that have been set, call ClearChannels.
*/
	ClearChannels();
	AddChannel( mALEChannel, "ALE", false );
	AddChannel( mCEChannel, "CE", false );
	AddChannel( mCLEChannel, "CLE", false );
	AddChannel( mLOCKChannel, "LOCK", false );
	AddChannel( mREChannel, "RE", false );
	AddChannel( mWEChannel, "WE", false );
	AddChannel( mWPChannel, "WP", false );
	AddChannel( mIOChannel, "I/O", false );
	AddChannel( mRBChannel, "RB", false );

}

/**
*  @brief Destructor
* @details we won't to do anything
*************************/
ONFIAnalyzerSettings::~ONFIAnalyzerSettings()
{
}

/**
*  @brief this function will copy the values saved in our interface ojbects to
*  our settings variables
**********************/
/*
For example, when using more than one channel,
you would typically want to make
 sure that all the channels are different.
You can use the AnalyzerHelpers::DoChannelsOverlap
function to make that easier if you like

à faire
*/
bool ONFIAnalyzerSettings::SetSettingsFromInterfaces()
{
	mALEChannel = mALEChannelInterface->GetChannel();
	//mBitRate = mBitRateInterface->GetInteger();
	ClearChannels();
	AddChannel( mALEChannel, "Protocole-ONFI", true );
	return true;
}

/**
*  @brief this function will copy the values saved in our interface ojbects to
*  our settings variables
**********************/

void ONFIAnalyzerSettings::UpdateInterfacesFromSettings()
{
		mALEChannelInterface->SetChannel( mALEChannel );
		mCEChannelInterface->SetChannel( mCEChannel );
		mCLEChannelInterface->SetChannel( mCLEChannel );
		mLOCKChannelInterface->SetChannel( mLOCKChannel );
		mREChannelInterface->SetChannel( mREChannel );
		mWEChannelInterface->SetChannel( mWEChannel );
		mWPChannelInterface->SetChannel( mWPChannel );
		mIOChannelInterface->SetChannel( mIOChannel );
		mRBChannelInterface->SetChannel( mRBChannel );

}

/**
*  @brief this function will  serialize all variables set upped
*
******/

void ONFIAnalyzerSettings::LoadSettings( const char* settings )
{
	// object used for serialize the variables
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> mALEChannel;
	text_archive >> mCEChannel;
	text_archive >> mCLEChannel;
	text_archive >> mLOCKChannel;
	text_archive >> mREChannel;
	text_archive >> mWEChannel;
	text_archive >> mWPChannel;
	text_archive >> mIOChannel;
	text_archive >> mRBChannel;
/// @brief  Since our channel values may have changed, we will also need to update the channels we’re reporting as using. We need to do this every times settings change.
	ClearChannels();
	AddChannel( mALEChannel, "Protocole-ONFI", mALEChannel != UNDEFINED_CHANNEL );
	AddChannel( mCEChannel, "Protocole-ONFI", mCEChannel != UNDEFINED_CHANNEL );
	AddChannel( mCLEChannel, "Protocole-ONFI", mCLEChannel != UNDEFINED_CHANNEL );
	AddChannel( mLOCKChannel, "Protocole-ONFI", mLOCKChannel != UNDEFINED_CHANNEL );
	AddChannel( mREChannel, "Protocole-ONFI", mREChannel != UNDEFINED_CHANNEL );
	AddChannel( mWEChannel, "Protocole-ONFI", mWEChannel != UNDEFINED_CHANNEL );
	AddChannel( mWPChannel, "Protocole-ONFI", mWPChannel != UNDEFINED_CHANNEL );
	AddChannel( mIOChannel, "Protocole-ONFI", mIOChannel != UNDEFINED_CHANNEL );
	AddChannel( mRBChannel, "Protocole-ONFI", mRBChannel != UNDEFINED_CHANNEL );
 /// @bried This will update all our interfaces to reflect the newly loaded values.
	UpdateInterfacesFromSettings();
}

/**
* @breif this function will save all of our settings variables into a single string
*****/
const char* ONFIAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mALEChannel;
	text_archive << mCEChannel;
	text_archive << mCLEChannel;
	text_archive << mLOCKChannel;
	text_archive << mREChannel;
	text_archive << mWEChannel;
	text_archive << mWPChannel;
	text_archive << mIOChannel;
	text_archive << mRBChannel;

	return SetReturnString( text_archive.GetString() );
}
