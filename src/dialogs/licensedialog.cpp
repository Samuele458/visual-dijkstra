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

#include "licensedialog.h"

LicenseDialog::LicenseDialog(QWidget *parent) : QDialog(parent)
{
    this->setMinimumWidth(650);

    //creating widgets
    MainLayout = new QVBoxLayout;
    TitleLabel = new QLabel;
    LicenseEdit = new QTextEdit;
    ButtonsLayout = new QHBoxLayout;
    OkButton = new QPushButton;

    ButtonsLayout->addStretch();
    ButtonsLayout->addWidget( OkButton );

    MainLayout->addWidget( TitleLabel );
    MainLayout->addWidget( LicenseEdit );
    MainLayout->addLayout( ButtonsLayout );

    this->setLayout( MainLayout );
    this->setWindowTitle( "License" );

    TitleLabel->setAlignment( Qt::AlignCenter );


    // --- configurating widgets ---

    QFile license_file( ":/data/LICENSE" );

    license_file.open( QIODevice::ReadOnly );
    LicenseEdit->setText( license_file.readAll() );
    OkButton->setText( tr( "Ok" ) );
    TitleLabel->setText( "GNU General Public License v3.0" );

    QFont title_font = TitleLabel->font();
    title_font.setPointSize( 25 );
    TitleLabel->setFont( title_font );

    LicenseEdit->setReadOnly( true );

    QFont licenseFont = LicenseEdit->font();
    licenseFont.setFamily( "Courier" );
    licenseFont.setPointSize(6);
    LicenseEdit->setFont(licenseFont);


    //OK button
    connect( OkButton, SIGNAL(clicked()), this, SLOT(ok_button_clicked()));

}

void LicenseDialog::ok_button_clicked() {
    this->close();
}
