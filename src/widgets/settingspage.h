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
#include <QPainter>
#include <QPaintEvent>
#include <QGroupBox>
#include <QGridLayout>
#include <QComboBox>
#include <QCheckBox>

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

    //apply state to widget
    virtual void applyState() { }

    //store settings from currentState to SettingsPage
    virtual void saveState();

private:
    SettingsManager* settings;
    QString scope;

protected:
    QHash<QString,QVariant> currentState;


};

class ColorButton : public QPushButton {
    Q_OBJECT

public:
    ColorButton( QColor color, QWidget* parent = nullptr );

    QColor getColor() const;
    void setColor( QColor color );

signals:
    void colorChanged(QColor);

public slots:
    void changeColor(const QColor &);
    void chooseColor();
    void paintEvent(QPaintEvent *event);

private:
    QColor color;

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


private slots:
    void color_changed( QColor color );


private:
    QColor color;

    QHBoxLayout* mainLayout;
    ColorButton* colorPickerButton;
    QLabel* textLabel;
    QLabel* labelColor;
};


class StylePage : public SettingsPage
{
    Q_OBJECT

public:
    StylePage(SettingsManager* settings,
              QWidget *parent = nullptr);

    void applyState() override;

    void saveState() override;
private slots:
    void colors_preset_state_changed( int state );

private:
    QLabel* colorsPresetLabel;

    QHBoxLayout* colorsPresetWrap;

    QComboBox* colorsPresetCombo;
    QCheckBox* customColorsCheckbox;

    ColorHandler* bgColorHandler;
    ColorHandler* textColorHandler;
    ColorHandler* nodesColorHandler;
    ColorHandler* edgesColorHandler;
    ColorHandler* pathColorHandler;
    ColorHandler* highlightColorHandler;

};


class DefaultPage : public SettingsPage
{
    Q_OBJECT

public:
    DefaultPage(SettingsManager* settings,
              QWidget *parent = nullptr);

};

#endif // SETTINGSPAGE_H








