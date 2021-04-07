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

#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QLabel>

#include "common/settingsmanager.h"

class SettingsPageError : public Error {
public:
    enum id {
        GENERIC,
        INVALID_ARGUMENT,

        INVALID_SETTINGS_MANAGER

    };

    SettingsPageError( id error_id = GENERIC, QString message = "" ) :
        Error( (Error::id)error_id, message ) { }
};


/*
 *  Handle a page of SettingsDialog, so
 *  it handles setting of a specific scope
 */
class SettingsPage : public QWidget
{
    Q_OBJECT
public:
    SettingsPage(SettingsManager* settings,
                 QString scope,
                 QWidget *parent = nullptr);

    //read settings from SettingsPage to currentState
    void loadState();

    //store settings from cerrentState to SettingsPage
    void saveState();

private:
    SettingsManager* settings;
    QString scope;
    QHash<QString,QVariant> currentState;


};

class ColorHandler : public QWidget {
    Q_OBJECT

public:
    ColorHandler( QString text, QWidget* parent = nullptr );
    ColorHandler( QString text, QColor color, QWidget* parent = nullptr );

    void setColor( QColor color );
    QColor getColor() const;

    void setText( QString text );
    QString getText() const;

private:
    QColor color;

    QHBoxLayout* mainLayout;
    QPushButton* colorPickerButton;
    QLabel* textLabel;
    QLabel* labelColor;
};


class StylePage : public SettingsPage
{
    Q_OBJECT

public:
    StylePage(SettingsManager* settings,
              QWidget *parent = nullptr);

};


class DefaultPage : public SettingsPage
{
    Q_OBJECT

public:
    DefaultPage(SettingsManager* settings,
              QWidget *parent = nullptr);

};

#endif // SETTINGSPAGE_H








