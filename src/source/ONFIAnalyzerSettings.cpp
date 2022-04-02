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
:	mALEChannel( UNDEFINED_CHANNEL ),
	mCEChannel( UNDEFINED_CHANNEL ),
	mCLEChannel( UNDEFINED_CHANNEL ),
	mREChannel( UNDEFINED_CHANNEL ),
	mWEChannel( UNDEFINED_CHANNEL ),
	mDQChannel( UNDEFINED_CHANNEL ),
	mRBChannel( UNDEFINED_CHANNEL ),
	mDQSChannel(UNDEFINED_CHANNEL),
	mDQ_1Channel( UNDEFINED_CHANNEL ),
	mDQ_2Channel( UNDEFINED_CHANNEL ),
	mDQ_3Channel( UNDEFINED_CHANNEL ),
	mDQ_4Channel( UNDEFINED_CHANNEL ),
	mDQ_5Channel( UNDEFINED_CHANNEL ),
	mDQ_6Channel( UNDEFINED_CHANNEL ),
	mDQ_7Channel( UNDEFINED_CHANNEL )
{
    /// @details Setting up each AnalyzerSettingInterface object
		// for the moment only AnalyzerSettingInterfaceChannel
		mALEChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mALEChannelInterface->SetTitleAndTooltip( "ALE", "Address latch enable" );
		mALEChannelInterface->SetChannel( mALEChannel );
		mALEChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mCEChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mCEChannelInterface->SetTitleAndTooltip( "CE", "Chip enable" );
		mCEChannelInterface->SetChannel( mCEChannel );
		mCEChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mCLEChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mCLEChannelInterface->SetTitleAndTooltip( "CLE", "Command latch enable" );
		mCLEChannelInterface->SetChannel( mCLEChannel );
		mCLEChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mREChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mREChannelInterface->SetTitleAndTooltip( "RE", "READ enable" );
		mREChannelInterface->SetChannel( mREChannel );
		mREChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mWEChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mWEChannelInterface->SetTitleAndTooltip( "WE", "Write enable " );
		mWEChannelInterface->SetChannel( mWEChannel );
		mWEChannelInterface->SetSelectionOfNoneIsAllowed( true );


		mDQChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mDQChannelInterface->SetTitleAndTooltip( "IO", "I/O, Data inputs/outputs" );
		mDQChannelInterface->SetChannel( mDQChannel );
		mDQChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mRBChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mRBChannelInterface->SetTitleAndTooltip( "RB", "Ready/busy" );
		mRBChannelInterface->SetChannel( mRBChannel );
		mRBChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mDQSChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mDQSChannelInterface->SetTitleAndTooltip( "DQS", "DQS" );
		mDQSChannelInterface->SetChannel( mDQSChannel );
		mDQSChannelInterface->SetSelectionOfNoneIsAllowed( true );


		//******************************//

				mDQ_1ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
				mDQ_1ChannelInterface->SetTitleAndTooltip( "Data", "data" );
				mDQ_1ChannelInterface->SetChannel( mDQ_1Channel );
				mDQ_1ChannelInterface->SetSelectionOfNoneIsAllowed( true );

				mDQ_2ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
				mDQ_2ChannelInterface->SetTitleAndTooltip( "Data", "data" );
				mDQ_2ChannelInterface->SetChannel( mDQ_2Channel );
				mDQ_2ChannelInterface->SetSelectionOfNoneIsAllowed( true );

				mDQ_3ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
				mDQ_3ChannelInterface->SetTitleAndTooltip( "Data", "data" );
				mDQ_3ChannelInterface->SetChannel( mDQ_3Channel );
				mDQ_3ChannelInterface->SetSelectionOfNoneIsAllowed( true );

				mDQ_4ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
				mDQ_4ChannelInterface->SetTitleAndTooltip( "Data", "data" );
				mDQ_4ChannelInterface->SetChannel( mDQ_4Channel );
				mDQ_4ChannelInterface->SetSelectionOfNoneIsAllowed( true );

				mDQ_5ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
				mDQ_5ChannelInterface->SetTitleAndTooltip( "Data", "data" );
				mDQ_5ChannelInterface->SetChannel( mDQ_5Channel );
				mDQ_5ChannelInterface->SetSelectionOfNoneIsAllowed( true );

				mDQ_6ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
				mDQ_6ChannelInterface->SetTitleAndTooltip( "Data", "data" );
				mDQ_6ChannelInterface->SetChannel( mDQ_6Channel );
				mDQ_6ChannelInterface->SetSelectionOfNoneIsAllowed( true );

				mDQ_7ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
				mDQ_7ChannelInterface->SetTitleAndTooltip( "Data", "data" );
				mDQ_7ChannelInterface->SetChannel( mDQ_7Channel );
				mDQ_7ChannelInterface->SetSelectionOfNoneIsAllowed( true );

				//*****************************//

		AddInterface( mALEChannelInterface.get() );
		AddInterface( mCEChannelInterface.get() );
		AddInterface( mCLEChannelInterface.get() );
		AddInterface( mREChannelInterface.get() );
		AddInterface( mWEChannelInterface.get() );
		AddInterface( mDQChannelInterface.get() );
		AddInterface( mRBChannelInterface.get() );
		AddInterface( mDQSChannelInterface.get() );


		AddInterface( mDQ_1ChannelInterface.get() );
		AddInterface( mDQ_2ChannelInterface.get() );
		AddInterface( mDQ_3ChannelInterface.get() );
		AddInterface( mDQ_4ChannelInterface.get() );
		AddInterface( mDQ_5ChannelInterface.get() );
		AddInterface( mDQ_6ChannelInterface.get() );
		AddInterface( mDQ_7ChannelInterface.get() );



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
	AddChannel( mREChannel, "RE", false );
	AddChannel( mWEChannel, "WE", false );
	AddChannel( mDQChannel, "I/O", false );
	AddChannel( mRBChannel, "RB", false );
	AddChannel( mDQSChannel, "DQS", false );


	AddChannel( mDQ_1Channel, "DQ", false );
	AddChannel( mDQ_2Channel, "DQ", false );
	AddChannel( mDQ_3Channel, "DQ", false );
	AddChannel( mDQ_4Channel, "DQ", false );
	AddChannel( mDQ_5Channel, "DQ", false );
	AddChannel( mDQ_6Channel, "DQ", false );
	AddChannel( mDQ_7Channel, "DQ", false );

}

/**
*  @brief Destructor
* @details we won't to do anything
*************************/
ONFIAnalyzerSettings::~ONFIAnalyzerSettings()
{
}

/**
*  @brief this function will copy the values saved in our interface objects to
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
	mCEChannel = mCEChannelInterface->GetChannel();
	mCLEChannel = mCLEChannelInterface->GetChannel();
	mREChannel = mREChannelInterface->GetChannel();
	mWEChannel = mWEChannelInterface->GetChannel();
	mDQChannel = mDQChannelInterface->GetChannel();
	mRBChannel = mRBChannelInterface->GetChannel();
	mDQSChannel = mDQSChannelInterface->GetChannel();

	bool has_dq=false;
  /**** ajouter la verification que chaque signal est
			dans un channel different
	***/

	// mettre à jour les signal qu'ont été ajouté sur l'interface
	ClearChannels();
	AddChannel( mALEChannel, "ALE", mALEChannel!=UNDEFINED_CHANNEL );
	AddChannel( mCEChannel, "CE", mCEChannel!=UNDEFINED_CHANNEL );
	AddChannel( mCLEChannel, "CLE", mCLEChannel!=UNDEFINED_CHANNEL );
	AddChannel( mREChannel, "RE", mREChannel!=UNDEFINED_CHANNEL );
	AddChannel( mWEChannel, "WE", mWEChannel!=UNDEFINED_CHANNEL );
	AddChannel( mDQChannel, "IO", mDQChannel!=UNDEFINED_CHANNEL );
	AddChannel( mRBChannel, "RB", mRBChannel!=UNDEFINED_CHANNEL );
	AddChannel( mDQSChannel, "DQS", mDQSChannel!=UNDEFINED_CHANNEL );


	AddChannel( mDQ_1Channel, "IO", mDQChannel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_2Channel, "IO", mDQChannel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_3Channel, "IO", mDQChannel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_4Channel, "IO", mDQChannel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_5Channel, "IO", mDQChannel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_6Channel, "IO", mDQChannel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_7Channel, "IO", mDQChannel!=UNDEFINED_CHANNEL );

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
		mREChannelInterface->SetChannel( mREChannel );
		mWEChannelInterface->SetChannel( mWEChannel );
		mDQChannelInterface->SetChannel( mDQChannel );
		mRBChannelInterface->SetChannel( mRBChannel );
		mDQSChannelInterface->SetChannel( mDQSChannel );


		mDQ_1ChannelInterface->SetChannel( mDQ_1Channel );
		mDQ_2ChannelInterface->SetChannel( mDQ_2Channel );
		mDQ_3ChannelInterface->SetChannel( mDQ_3Channel );
		mDQ_4ChannelInterface->SetChannel( mDQ_4Channel );
		mDQ_5ChannelInterface->SetChannel( mDQ_5Channel );
		mDQ_6ChannelInterface->SetChannel( mDQ_6Channel );
		mDQ_7ChannelInterface->SetChannel( mDQ_7Channel );

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
	text_archive >> mREChannel;
	text_archive >> mWEChannel;
	text_archive >> mDQChannel;
	text_archive >> mRBChannel;
	text_archive >> mDQSChannel;


	text_archive >> mDQ_1Channel;
	text_archive >> mDQ_2Channel;
	text_archive >> mDQ_3Channel;
	text_archive >> mDQ_4Channel;
	text_archive >> mDQ_5Channel;
	text_archive >> mDQ_6Channel;
	text_archive >> mDQ_7Channel;
/// @brief  Since our channel values may have changed, we will also need to update the channels we’re reporting as using. We need to do this every times settings change.
	ClearChannels();
	AddChannel( mALEChannel, "ALE", mALEChannel != UNDEFINED_CHANNEL );
	AddChannel( mCEChannel, "CE", mCEChannel != UNDEFINED_CHANNEL );
	AddChannel( mCLEChannel, "CLE", mCLEChannel != UNDEFINED_CHANNEL );
	AddChannel( mREChannel, "RE", mREChannel != UNDEFINED_CHANNEL );
	AddChannel( mWEChannel, "WE", mWEChannel != UNDEFINED_CHANNEL );
	AddChannel( mDQChannel, "IO", mDQChannel != UNDEFINED_CHANNEL );
	AddChannel( mRBChannel, "RB", mRBChannel != UNDEFINED_CHANNEL );
	AddChannel( mDQSChannel, "DQS", mDQSChannel != UNDEFINED_CHANNEL );


	AddChannel( mDQ_1Channel, "Protocole-ONFI", mDQChannel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_2Channel, "Protocole-ONFI", mDQChannel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_3Channel, "Protocole-ONFI", mDQChannel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_4Channel, "Protocole-ONFI", mDQChannel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_5Channel, "Protocole-ONFI", mDQChannel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_6Channel, "Protocole-ONFI", mDQChannel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_7Channel, "Protocole-ONFI", mDQChannel != UNDEFINED_CHANNEL );

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
	text_archive << mREChannel;
	text_archive << mWEChannel;
	text_archive << mDQChannel;
	text_archive << mRBChannel;
	text_archive << mDQSChannel;


	text_archive << mDQ_1Channel;
	text_archive << mDQ_2Channel;
	text_archive << mDQ_3Channel;
	text_archive << mDQ_4Channel;
	text_archive << mDQ_5Channel;
	text_archive << mDQ_6Channel;
	text_archive << mDQ_7Channel;

	return SetReturnString( text_archive.GetString() );
}
