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


// ---- class StylePage ----




StylePage::StylePage(SettingsManager *settings, QString scope, QWidget *parent) :
    SettingsPage( settings, scope, parent )
{

    QPushButton* button = new QPushButton("TEST");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget( button );

    this->setLayout( mainLayout );

}






