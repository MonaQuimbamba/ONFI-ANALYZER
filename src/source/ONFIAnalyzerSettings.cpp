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
:	 mALEChannel( UNDEFINED_CHANNEL )
{

		mALEChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mALEChannelInterface->SetTitleAndTooltip( "ALE", "INPUT , Address latch enable" );
		mALEChannelInterface->SetChannel( mALEChannel );
		mALEChannelInterface->SetSelectionOfNoneIsAllowed( true );


	AddInterface( mALEChannelInterface.get() );
	/*AddInterface( mCEChannelInterface.get() );
	AddInterface( mCLEChannelInterface.get() );
	AddInterface( mLOCKChannelInterface.get() );
	AddInterface( mREChannelInterface.get() );
	AddInterface( mWEChannelInterface.get() );
	AddInterface( mWPChannelInterface.get() );
	AddInterface( mIOChannelInterface.get() );
	AddInterface( mRBChannelInterface.get() );*/


	//AddInterface( mBitRateInterface.get() );

//****************** Export datas
	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	ClearChannels();
	AddChannel( mALEChannel, "ALE", false );

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
	//mBitRateInterface->SetInteger( mBitRate );*/
}

void ONFIAnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> mALEChannel;
	//text_archive >> mBitRate;

	ClearChannels();
	AddChannel( mALEChannel, "Protocole-ONFI", true );

	UpdateInterfacesFromSettings();
}

const char* ONFIAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mALEChannel;
	//text_archive << mBitRate;

	return SetReturnString( text_archive.GetString() );
}
