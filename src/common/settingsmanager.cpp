/*          Visual Dijkstra
 *    Copyright (C) 2021 Samuele Girgenti
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * 	     --  CONTACTS --
 *   Email:      samuele.girgenti458@gmail.com
 *   Github:     https://github.com/Samuele458
 */

#include "settingsmanager.h"

//default settings file
const QString SettingsManager::DEFAULT_SETTINGS_FILENAME = ":/data/default_settings.ini";

SettingsManager::SettingsManager(QString filename)
{

    if( QFile::exists( SettingsManager::DEFAULT_SETTINGS_FILENAME ) )
    {
        if( QFile::exists( filename ) ) {
            this->settings = new QSettings( filename, QSettings::IniFormat );
            this->defaultSettings =
               new QSettings( DEFAULT_SETTINGS_FILENAME, QSettings::IniFormat );

        } else {
            throw SettingsManagerError(
                        SettingsManagerError::FILE_DOES_NOT_EXIST,
                        "File does not exist"
                  );
        }
    } else {
        //exception: default config file does not exist
        throw SettingsManagerError(
                    SettingsManagerError::DEFAULT_CONFIG_FILE_DOES_NOT_EXIST,
                    "Default file does not exist"
              );
    }


}


//return filename string
QString SettingsManager::getFilename() const {
    return filename;
}

void SettingsManager::setValue( const QString& scope, const QString& key, const QVariant& data ) {

    //checking if scope exists in settings, or in defaultSettings
    if( defaultSettings->childGroups().indexOf(scope) == -1 ) {
        throw SettingsManagerError(
                    SettingsManagerError::UNKNOWN_SCOPE,
                    "Unknown scope"
              );
    }

    //checking if key exists
    defaultSettings->beginGroup( scope );
    if( defaultSettings->childKeys().indexOf(key) == -1 ) {
        defaultSettings->endGroup();
        throw SettingsManagerError(
                    SettingsManagerError::UNKNOWN_KEY,
                    "Unknown key"
              );
    }
    defaultSettings->endGroup();

    //open selected group
    settings->beginGroup( scope );
    settings->setValue( key, data );
    settings->endGroup();
}

QVariant SettingsManager::getValue( QString& scope, QString& key ) {
    settings->beginGroup( scope );
    QVariant data = settings->value( key );
    settings->endGroup();

    return data;
}


