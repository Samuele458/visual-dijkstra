#include "settingspage.h"

SettingsPage::SettingsPage( SettingsManager* settings,
                            QString scope,
                            QWidget *parent ) :
    QWidget(parent)
{
    if( settings != nullptr &&
        settings->hasScope( scope )) {

        this->settings = settings;
        this->scope = scope;

    } else {
        throw SettingsPageError(
                    SettingsPageError::INVALID_SETTINGS_MANAGER,
                    "Invalid SettingsManager"
              );
    }
}
