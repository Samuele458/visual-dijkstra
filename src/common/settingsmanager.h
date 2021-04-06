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

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QSettings>
#include <QColor>
#include <QFile>
#include <QDebug>


#include "common/error.h"

class SettingsManagerError : public Error {
public:
    enum id {
        GENERIC,
        INVALID_ARGUMENT,

        FILE_DOES_NOT_EXIST,
        DEFAULT_CONFIG_FILE_DOES_NOT_EXIST,
        UNKNOWN_SCOPE,
        UNKNOWN_KEY
    };

    SettingsManagerError( id error_id = GENERIC, QString message = "" ) :
        Error( (Error::id)error_id, message ) { }
};


/*
 *  Handle settings for the entire application, every read / write
 * to the settings must reference the instance of this class
 */
class SettingsManager
{

public:

    //default settings file
    static const QString DEFAULT_SETTINGS_FILENAME;

    SettingsManager( QString filename );

    //TODO: add destructor. QSettings are dinamically allocated

    //return filename string
    QString getFilename() const;

    void setFileName( QString filename );

    // write value to QSettings
    void setValue( const QString& scope, const QString& key, const QVariant& data );

    //read value from QSettings
    QVariant getValue( const QString& scope, const QString& key );

    bool hasScope( QString scope );
    bool hasKey( QString scope, QString key );

    QStringList getScopes();
    QStringList getKeys( QString scope );

private:
    QSettings* settings;
    QSettings* defaultSettings;
    QString filename;
};

#endif // SETTINGSMANAGER_H
