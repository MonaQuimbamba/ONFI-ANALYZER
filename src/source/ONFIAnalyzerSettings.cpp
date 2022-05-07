#include "ONFIAnalyzerSettings.h"
#include <AnalyzerHelpers.h>




ONFIAnalyzerSettings::ONFIAnalyzerSettings()
:	mALEChannel( UNDEFINED_CHANNEL ),
	mCEChannel( UNDEFINED_CHANNEL ),
	mCLEChannel( UNDEFINED_CHANNEL ),
	mREChannel( UNDEFINED_CHANNEL ),
	mWEChannel( UNDEFINED_CHANNEL ),
<<<<<<< HEAD
	mDQSChannel(UNDEFINED_CHANNEL)
=======
	mRBChannel( UNDEFINED_CHANNEL ),
	mDQSChannel(UNDEFINED_CHANNEL),
	mDQChannel( UNDEFINED_CHANNEL ),
	mDQ_1Channel( UNDEFINED_CHANNEL ),
	mDQ_2Channel( UNDEFINED_CHANNEL ),
	mDQ_3Channel( UNDEFINED_CHANNEL ),
	mDQ_4Channel( UNDEFINED_CHANNEL ),
	mDQ_5Channel( UNDEFINED_CHANNEL ),
	mDQ_6Channel( UNDEFINED_CHANNEL ),
	mDQ_7Channel( UNDEFINED_CHANNEL )
>>>>>>> version_1
{

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

<<<<<<< HEAD

		mDQSChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mDQSChannelInterface->SetTitleAndTooltip( "DQS ", "Data strobe  " );
		mDQSChannelInterface->SetChannel( mDQSChannel );
		mDQSChannelInterface->SetSelectionOfNoneIsAllowed( true );


=======
		mRBChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mRBChannelInterface->SetTitleAndTooltip( "RB", "Ready/busy" );
		mRBChannelInterface->SetChannel( mRBChannel );
		mRBChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mDQSChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mDQSChannelInterface->SetTitleAndTooltip(  "DQS ", "Data" );
		mDQSChannelInterface->SetChannel( mDQSChannel );
		mDQSChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mDQChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mDQChannelInterface->SetTitleAndTooltip( "DQ0", "data" );
		mDQChannelInterface->SetChannel( mDQChannel );
		mDQChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mDQ_1ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mDQ_1ChannelInterface->SetTitleAndTooltip( "DQ1", "data" );
		mDQ_1ChannelInterface->SetChannel( mDQ_1Channel );
		mDQ_1ChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mDQ_2ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mDQ_2ChannelInterface->SetTitleAndTooltip( "DQ2", "data" );
		mDQ_2ChannelInterface->SetChannel( mDQ_2Channel );
		mDQ_2ChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mDQ_3ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mDQ_3ChannelInterface->SetTitleAndTooltip( "DQ3", "data" );
		mDQ_3ChannelInterface->SetChannel( mDQ_3Channel );
		mDQ_3ChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mDQ_4ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mDQ_4ChannelInterface->SetTitleAndTooltip( "DQ4", "data" );
		mDQ_4ChannelInterface->SetChannel( mDQ_4Channel );
		mDQ_4ChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mDQ_5ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mDQ_5ChannelInterface->SetTitleAndTooltip( "DQ5", "data" );
		mDQ_5ChannelInterface->SetChannel( mDQ_5Channel );
		mDQ_5ChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mDQ_6ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mDQ_6ChannelInterface->SetTitleAndTooltip( "DQ6", "data" );
		mDQ_6ChannelInterface->SetChannel( mDQ_6Channel );
		mDQ_6ChannelInterface->SetSelectionOfNoneIsAllowed( true );

		mDQ_7ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
		mDQ_7ChannelInterface->SetTitleAndTooltip( "DQ7", "data" );
		mDQ_7ChannelInterface->SetChannel( mDQ_7Channel );
		mDQ_7ChannelInterface->SetSelectionOfNoneIsAllowed( true );
>>>>>>> version_1

		AddInterface( mALEChannelInterface.get() );
		AddInterface( mCEChannelInterface.get() );
		AddInterface( mCLEChannelInterface.get() );
		AddInterface( mREChannelInterface.get() );
		AddInterface( mWEChannelInterface.get() );
<<<<<<< HEAD
		AddInterface( mDQSChannelInterface.get());
=======
		AddInterface( mRBChannelInterface.get() );
		AddInterface( mDQSChannelInterface.get() );
>>>>>>> version_1

	  AddInterface( mDQChannelInterface.get() );
		AddInterface( mDQ_1ChannelInterface.get() );
		AddInterface( mDQ_2ChannelInterface.get() );
		AddInterface( mDQ_3ChannelInterface.get() );
		AddInterface( mDQ_4ChannelInterface.get() );
		AddInterface( mDQ_5ChannelInterface.get() );
		AddInterface( mDQ_6ChannelInterface.get() );
		AddInterface( mDQ_7ChannelInterface.get() );


	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );


	ClearChannels();
	AddChannel( mALEChannel, "ALE", false );
	AddChannel( mCEChannel, "CE", false );
	AddChannel( mCLEChannel, "CLE", false );
	AddChannel( mREChannel, "RE", false );
	AddChannel( mWEChannel, "WE", false );
<<<<<<< HEAD
		AddChannel( mDQSChannel, "DQS", false );
=======
	AddChannel( mRBChannel, "RB", false );
	AddChannel( mDQSChannel, "DQS", false );
>>>>>>> version_1

	AddChannel( mDQChannel,   "DQ", false );
	AddChannel( mDQ_1Channel, "DQ", false );
	AddChannel( mDQ_2Channel, "DQ", false );
	AddChannel( mDQ_3Channel, "DQ", false );
	AddChannel( mDQ_4Channel, "DQ", false );
	AddChannel( mDQ_5Channel, "DQ", false );
	AddChannel( mDQ_6Channel, "DQ", false );
	AddChannel( mDQ_7Channel, "DQ", false );

}


ONFIAnalyzerSettings::~ONFIAnalyzerSettings()
{
}


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
<<<<<<< HEAD
	mDQSChannel= mDQSChannelInterface->GetChannel();
=======
	mRBChannel = mRBChannelInterface->GetChannel();
	mDQSChannel = mDQSChannelInterface->GetChannel();
>>>>>>> version_1

	mDQChannel = mDQChannelInterface->GetChannel();
	mDQ_1Channel = mDQ_1ChannelInterface->GetChannel();
	mDQ_2Channel = mDQ_2ChannelInterface->GetChannel();
	mDQ_3Channel = mDQ_3ChannelInterface->GetChannel();
	mDQ_4Channel = mDQ_4ChannelInterface->GetChannel();

	mDQ_5Channel = mDQ_5ChannelInterface->GetChannel();
	mDQ_6Channel = mDQ_6ChannelInterface->GetChannel();
	mDQ_7Channel = mDQ_7ChannelInterface->GetChannel();

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
<<<<<<< HEAD
	AddChannel( mDQSChannel, "DQS", mDQSChannel!=UNDEFINED_CHANNEL );


=======
	AddChannel( mRBChannel, "RB", mRBChannel!=UNDEFINED_CHANNEL );
	AddChannel( mDQSChannel, "DQS", mDQSChannel!=UNDEFINED_CHANNEL );


	AddChannel( mDQChannel, "DQ", mDQChannel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_1Channel, "DQ", mDQ_1Channel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_2Channel, "DQ", mDQ_2Channel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_3Channel, "DQ", mDQ_3Channel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_4Channel, "DQ", mDQ_4Channel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_5Channel, "DQ", mDQ_5Channel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_6Channel, "DQ", mDQ_6Channel!=UNDEFINED_CHANNEL );
	AddChannel( mDQ_7Channel, "DQ", mDQ_7Channel!=UNDEFINED_CHANNEL );

>>>>>>> version_1
	return true;
}

void ONFIAnalyzerSettings::UpdateInterfacesFromSettings()
{
		mALEChannelInterface->SetChannel( mALEChannel );
		mCEChannelInterface->SetChannel( mCEChannel );
		mCLEChannelInterface->SetChannel( mCLEChannel );
		mREChannelInterface->SetChannel( mREChannel );
		mWEChannelInterface->SetChannel( mWEChannel );
<<<<<<< HEAD
		mDQSChannelInterface->SetChannel( mDQSChannel );

=======
		mRBChannelInterface->SetChannel( mRBChannel );
		mDQSChannelInterface->SetChannel( mDQSChannel );

		mDQChannelInterface->SetChannel( mDQChannel );
		mDQ_1ChannelInterface->SetChannel( mDQ_1Channel );
		mDQ_2ChannelInterface->SetChannel( mDQ_2Channel );
		mDQ_3ChannelInterface->SetChannel( mDQ_3Channel );
		mDQ_4ChannelInterface->SetChannel( mDQ_4Channel );
		mDQ_5ChannelInterface->SetChannel( mDQ_5Channel );
		mDQ_6ChannelInterface->SetChannel( mDQ_6Channel );
		mDQ_7ChannelInterface->SetChannel( mDQ_7Channel );

>>>>>>> version_1
}


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
<<<<<<< HEAD
	text_archive >> mDQSChannel;

/// @brief  Since our channel values may have changed, we will also need to update the channels we’re reporting as using. We need to do this every times settings change.
=======
	text_archive >> mRBChannel;
	text_archive >> mDQSChannel;

	text_archive >> mDQChannel;
	text_archive >> mDQ_1Channel;
	text_archive >> mDQ_2Channel;
	text_archive >> mDQ_3Channel;
	text_archive >> mDQ_4Channel;
	text_archive >> mDQ_5Channel;
	text_archive >> mDQ_6Channel;
	text_archive >> mDQ_7Channel;

>>>>>>> version_1
	ClearChannels();
	AddChannel( mALEChannel, "ALE", mALEChannel != UNDEFINED_CHANNEL );
	AddChannel( mCEChannel, "CE", mCEChannel != UNDEFINED_CHANNEL );
	AddChannel( mCLEChannel, "CLE", mCLEChannel != UNDEFINED_CHANNEL );
	AddChannel( mREChannel, "RE", mREChannel != UNDEFINED_CHANNEL );
	AddChannel( mWEChannel, "WE", mWEChannel != UNDEFINED_CHANNEL );
<<<<<<< HEAD
	AddChannel( mDQSChannel,"DQS",mDQSChannel!=UNDEFINED_CHANNEL);

 /// @bried This will update all our interfaces to reflect the newly loaded values.
=======

	AddChannel( mRBChannel, "RB", mRBChannel != UNDEFINED_CHANNEL );
	AddChannel( mDQSChannel, "DQS", mDQSChannel != UNDEFINED_CHANNEL );

		AddChannel( mDQChannel, "DQ", mDQChannel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_1Channel, "DQ", mDQ_1Channel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_2Channel, "DQ", mDQ_2Channel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_3Channel, "DQ", mDQ_3Channel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_4Channel, "DQ", mDQ_4Channel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_5Channel, "DQ", mDQ_5Channel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_6Channel, "DQ", mDQ_6Channel != UNDEFINED_CHANNEL );
	AddChannel( mDQ_7Channel, "DQ", mDQ_7Channel != UNDEFINED_CHANNEL );
>>>>>>> version_1
	UpdateInterfacesFromSettings();
}


const char* ONFIAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mALEChannel;
	text_archive << mCEChannel;
	text_archive << mCLEChannel;
	text_archive << mREChannel;
	text_archive << mWEChannel;
<<<<<<< HEAD
	text_archive << mDQSChannel;

=======

	text_archive << mRBChannel;
	text_archive << mDQSChannel;

  text_archive << mDQChannel;
	text_archive << mDQ_1Channel;
	text_archive << mDQ_2Channel;
	text_archive << mDQ_3Channel;
	text_archive << mDQ_4Channel;
	text_archive << mDQ_5Channel;
	text_archive << mDQ_6Channel;
	text_archive << mDQ_7Channel;
>>>>>>> version_1

	return SetReturnString( text_archive.GetString() );
}
