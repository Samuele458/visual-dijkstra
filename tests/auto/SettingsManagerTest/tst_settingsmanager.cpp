#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QDebug>
#include <QtWidgets>
#include <QPushButton>
#include <QFile>
#include <QRegExp>

#include "common/settingsmanager.h"


class SettingsManagerTest : public QObject {
    Q_OBJECT

private slots:
    void constructByFilename_SettingsManagerCreated();
    void constructByUnknownFilename_ExceptionThrown();
    void setCorrectValue_ValueSet();
    void setUnknownValue_ExceptionThrown();
    void getCorrectValue_ValueSet();
    void getUnknownValue_ExceptionThrown();
};

void SettingsManagerTest::constructByFilename_SettingsManagerCreated() {

    //delete previous file
    QFile::remove("config.ini");

    QFile file("config.ini");
    file.open((QIODevice::ReadWrite));
    file.close();

    //if no exception is thrown means that filename is correct
    SettingsManager settings("config.ini");

}

void SettingsManagerTest::constructByUnknownFilename_ExceptionThrown() {
    QVERIFY_EXCEPTION_THROWN( SettingsManager("unknown_file.ini"), SettingsManagerError );
}

void SettingsManagerTest::setCorrectValue_ValueSet() {
    //delete previous file
    QFile::remove("config.ini");

    QFile file("config.ini");
    file.open((QIODevice::ReadWrite));
    file.close();

    //if no exception is thrown means that filename is correct
    SettingsManager settings("config.ini");

    settings.setValue("style","nodes-color", "#FFFFFF" );

}

void SettingsManagerTest::setUnknownValue_ExceptionThrown() {
    //delete previous file
    QFile::remove("config.ini");

    QFile file("config.ini");
    file.open((QIODevice::ReadWrite));
    file.close();

    //if no exception is thrown means that filename is correct
    SettingsManager settings("config.ini");

    QVERIFY_EXCEPTION_THROWN( settings.setValue("wrong-scope","preset","none"),
                              SettingsManagerError );
    QVERIFY_EXCEPTION_THROWN( settings.setValue("style","wrong-attribute","none"),
                              SettingsManagerError );
}

void SettingsManagerTest::getCorrectValue_ValueSet() {
    //delete previous file
    QFile::remove("config.ini");

    QFile file("config.ini");
    file.open((QIODevice::ReadWrite));
    file.close();

    //if no exception is thrown means that filename is correct
    SettingsManager settings("config.ini");

    QRegExp hexColorRegex("^\\#[0-9ABCDEF]{6}$");

    QVERIFY( hexColorRegex.exactMatch( settings.getValue("style","nodes-color").toString() ) );
}

void SettingsManagerTest::getUnknownValue_ExceptionThrown() {
    //delete previous file
    QFile::remove("config.ini");

    QFile file("config.ini");
    file.open((QIODevice::ReadWrite));
    file.close();

    //if no exception is thrown means that filename is correct
    SettingsManager settings("config.ini");

    QVERIFY_EXCEPTION_THROWN( settings.getValue("wrong-scope","preset"),
                              SettingsManagerError );

    QVERIFY_EXCEPTION_THROWN( settings.getValue("style","wrong-attribute"),
                              SettingsManagerError );
}



QTEST_MAIN(SettingsManagerTest)
#include "tst_settingsmanager.moc"
