#include "ONFIAnalyzerSettings.h"
#include "../AnalyzerSDK/include/AnalyzerHelpers.h"

/**
* @brief consctructor it'll build the settings for our analyzer , set up  each signal on one channel
*
*********************************/
ONFIAnalyzerSettings::ONFIAnalyzerSettings():

	 mALEChannel( UNDEFINED_CHANNEL ),
	 mCEChannel( UNDEFINED_CHANNEL ),
	 mCLEChannel( UNDEFINED_CHANNEL ),
	 mLOCKChannel( UNDEFINED_CHANNEL ),
	 mREChannel( UNDEFINED_CHANNEL ),
	 mWEChannel( UNDEFINED_CHANNEL ),
	 mWPChannel( UNDEFINED_CHANNEL ),
	 mIOChannel( UNDEFINED_CHANNEL ),
	 mRBChannel( UNDEFINED_CHANNEL ),
	 mBitRate( 9600 )
{


	mALEChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mALEChannelInterface->SetTitleAndTooltip( "ALE", "INPUT , Address latch enable" );
	mALEChannelInterface->SetChannel( mALEChannel );
	mALEChannelInterface->SetSelectionOfNoneIsAllowed( true );

	mCEChannel.reset( new AnalyzerSettingInterfaceChannel() );
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


	//****************



	mBitRateInterface.reset( new AnalyzerSettingInterfaceInteger() );
	mBitRateInterface->SetTitleAndTooltip( "Bit Rate (Bits/S)",  "Specify the bit rate in bits per second." );
	mBitRateInterface->SetMax( 6000000 );
	mBitRateInterface->SetMin( 1 );
	mBitRateInterface->SetInteger( mBitRate );

	//****

	AddInterface( mALEChannelInterface.get() );
	AddInterface( mCEChannelInterface.get() );
	AddInterface( mCLEChannelInterface.get() );
	AddInterface( mLOCKChannelInterface.get() );
	AddInterface( mREChannelInterface.get() );
	AddInterface( mWEChannelInterface.get() );
	AddInterface( mWPChannelInterface.get() );
	AddInterface( mIOChannelInterface.get() );
	AddInterface( mRBChannelInterface.get() );


	AddInterface( mBitRateInterface.get() );

//****************** Export datas
	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

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
*  @brief Destructor we won't to do anything
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
	mInputChannel = mInputChannelInterface->GetChannel();
	mBitRate = mBitRateInterface->GetInteger();

	ClearChannels();
	AddChannel( mInputChannel, "Protocole-ONFI", true );

	return true;
}

void ONFIAnalyzerSettings::UpdateInterfacesFromSettings()
{
	mInputChannelInterface->SetChannel( mInputChannel );
	mBitRateInterface->SetInteger( mBitRate );
}

void ONFIAnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> mInputChannel;
	text_archive >> mBitRate;

	ClearChannels();
	AddChannel( mInputChannel, "Protocole-ONFI", true );

	UpdateInterfacesFromSettings();
}

const char* ONFIAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mInputChannel;
	text_archive << mBitRate;

	return SetReturnString( text_archive.GetString() );
}
