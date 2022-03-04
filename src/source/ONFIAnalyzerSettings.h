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
	
protected:
	/// @details the interface for the channel ALE
	std::auto_ptr< AnalyzerSettingInterfaceChannel > mALEChannelInterface;
};

#endif //ONFI_ANALYZER_SETTINGS
