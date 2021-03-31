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


    bool getValue( QString scope, QString name, QVariant data );


private:
    QSettings settings;
    QString filename;
};

#endif // SETTINGSMANAGER_H
