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


SettingsManager::SettingsManager(QString filename) :
    settings( filename, QSettings::IniFormat ),
    filename( filename )
{

}


//return filename string
QString SettingsManager::getFilename() const {
    return filename;
}

void SettingsManager::setValue( const QString& scope, const QString& name, const QVariant& data ) {
    settings.beginGroup( scope );
    settings.setValue( name, data );
    settings.endGroup();
}

QVariant SettingsManager::getValue( QString& scope, QString& name ) {
    settings.beginGroup( scope );
    QVariant data = settings.value( name );
    settings.endGroup();

    return data;
}


