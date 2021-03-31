#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include <QDebug>

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

#endif // SETTINGSPAGE_H
