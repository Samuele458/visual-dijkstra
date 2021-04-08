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

#include "settingspage.h"

// ---- class SettingsPage ----

SettingsPage::SettingsPage( SettingsManager* settings,
                            QString scope,
                            QWidget *parent ) :
    QWidget(parent)
{

    qDebug() << scope;
    if( settings != nullptr &&
        settings->hasScope( scope )) {

        this->settings = settings;
        this->scope = scope;

        //loading current state
        this->loadState();

    } else {
        throw SettingsPageError(
                    SettingsPageError::INVALID_SETTINGS_MANAGER,
                    "Invalid SettingsManager"
              );
    }
}

//read settings from SettingsPage to currentState
void SettingsPage::loadState() {
    QStringList keys = settings->getKeys( scope );

    //clearing previous values
    currentState.clear();

    QStringListIterator i(keys);
    while( i.hasNext() ) {
        QString key = i.next();
        currentState.insert( key, settings->getValue( scope, key ) );
    }
}

//store settings from currentState to SettingsPage
void SettingsPage::saveState() {
    QStringList keys = settings->getKeys( scope );

    QStringListIterator i(keys);
    while( i.hasNext() ) {
        QString key = i.next();
        settings->setValue( scope, key, currentState.value(key) );
    }
}

// ---- class ColorButton ----

ColorButton::ColorButton( QColor color, QWidget *parent) :
    QPushButton(parent)
{
    this->setMinimumWidth(50);
    this->color = color;
    connect(this, SIGNAL(clicked()), this, SLOT(chooseColor()));
}

QColor ColorButton::getColor() const
{
    return this->color;
}

void ColorButton::setColor( QColor color ) {
    this->color = color;
    colorChanged(color);
}

void ColorButton::changeColor(const QColor & color)
{
    this->color = color;
    colorChanged(color);
}

void ColorButton::chooseColor()
{
    QColor color = QColorDialog::getColor(this->color, this, "Choose a color");
    if (color.isValid())
        changeColor(color);
}

void ColorButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    int colorPadding = 5;

    QRect rect = event->rect();
    QPainter painter( this );
    painter.setBrush( QBrush( color ) );
    painter.setPen("#CECECE");
    rect.adjust(colorPadding, colorPadding, -1-colorPadding, -1-colorPadding);
    painter.drawRect(rect);
}

// ---- class ColorHandler ----

ColorHandler::ColorHandler( QString text, QWidget* parent ) :
    ColorHandler( text, QColor(), parent )
{ }

ColorHandler::ColorHandler( QString text, QColor color, QWidget* parent ) :
    QWidget( parent )
{
    this->color = color;

    textLabel = new QLabel;
    textLabel->setText(text);

    labelColor = new QLabel;
    labelColor->setText( color.name(QColor::NameFormat::HexRgb) );

    colorPickerButton = new ColorButton(this->color);
    connect( colorPickerButton, SIGNAL(colorChanged(QColor)), this, SLOT(color_changed(QColor)));

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(textLabel);
    mainLayout->addStretch();
    mainLayout->addWidget(labelColor);
    mainLayout->addStretch();
    mainLayout->addWidget(colorPickerButton);

    this->setLayout(mainLayout);

    // -----

}

void ColorHandler::setColor( QColor color ) {
    qDebug() << color;

    //this->colorPickerButton->getColor();
    //this->color = QColor(Qt::red);
}

QColor ColorHandler::getColor() const {
    return this->color;
}

void ColorHandler::setText( QString text ) {
    this->textLabel->setText(text);
}

QString ColorHandler::getText() const {
    return this->textLabel->text();
}

void ColorHandler::color_changed( QColor color ) {
    this->color = color;
    this->labelColor->setText( this->color.name(QColor::NameFormat::HexRgb));
}


// ---- class StylePage ----


StylePage::StylePage(SettingsManager *settings, QWidget *parent) :
    SettingsPage( settings, "style" , parent )
{   

    QLabel* colorsPresetLabel = new QLabel("Preset:");

    colorsPresetCombo = new QComboBox;
    colorsPresetCombo->addItems( QStringList() << "Light mode" << "Dark mode" );

    QHBoxLayout* colorsPresetWrap = new QHBoxLayout;
    colorsPresetWrap->addWidget(colorsPresetLabel);
    colorsPresetWrap->addWidget(colorsPresetCombo);

    customColorsCheckbox = new QCheckBox("Custom");
    connect( customColorsCheckbox, SIGNAL(stateChanged(int)), this, SLOT(colors_preset_state_changed(int)));
    customColorsCheckbox->setCheckState(Qt::CheckState::Unchecked);

    bgColorHandler = new ColorHandler( "Background color:", QColor(this->currentState["widgets-background-color"].toString()) );
    textColorHandler = new ColorHandler( "Text color:", QColor(this->currentState["widgets-text-color"].toString()) );
    nodesColorHandler = new ColorHandler( "Nodes color:", QColor(this->currentState["nodes-color"].toString()) );
    edgesColorHandler = new ColorHandler( "Edges color:", QColor(this->currentState["edges-color"].toString()) );

    this->bgColorHandler->getColor();


    QVBoxLayout* colorsGroupLayout = new QVBoxLayout;
    colorsGroupLayout->addLayout(colorsPresetWrap);
    colorsGroupLayout->addWidget(customColorsCheckbox);
    colorsGroupLayout->addWidget(bgColorHandler);
    colorsGroupLayout->addWidget(textColorHandler);
    colorsGroupLayout->addWidget(nodesColorHandler);
    colorsGroupLayout->addWidget(edgesColorHandler);

    QGroupBox* colorsGroup = new QGroupBox("Colors");
    colorsGroup->setLayout( colorsGroupLayout );

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget( colorsGroup );

    this->setLayout( mainLayout );

    qDebug() << "Current state:" << this->currentState;

    QString d = this->currentState["widgets-background-color"].toString();

}

void StylePage::colors_preset_state_changed( int state ) {
    qDebug() << "STATE:" << state;
}


// ---- class DefaultPage ----

//TODO: UI Background color

DefaultPage::DefaultPage(SettingsManager *settings, QWidget *parent) :
    SettingsPage( settings, "style" , parent )
{

    QPushButton* button = new QPushButton("TEST");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget( button );
    mainLayout->addWidget(new QPushButton("TEST"));

    this->setLayout( mainLayout );

}






