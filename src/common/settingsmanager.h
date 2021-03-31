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

/*
 *  Handle settings for the entire application, every read / write
 * to the settings must reference the instance of this class
 */
class SettingsManager
{

public:
    SettingsManager( QString filename );

    //return filename string
    QString getFilename() const;

    // write value to QSettings
    void setValue( const QString& scope, const QString& name, const QVariant& data );

    //read value from QSettings
    QVariant getValue( QString& scope, QString& name );


private:
    QSettings settings;
    QString filename;
};

#endif // SETTINGSMANAGER_H
