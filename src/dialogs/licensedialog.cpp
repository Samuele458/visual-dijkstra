#include "licensedialog.h"

LicenseDialog::LicenseDialog(QWidget *parent) : QDialog(parent)
{

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


    //OK button
    connect( OkButton, SIGNAL(clicked()), this, SLOT(ok_button_clicked()));

}

void LicenseDialog::ok_button_clicked() {
    this->close();
}
