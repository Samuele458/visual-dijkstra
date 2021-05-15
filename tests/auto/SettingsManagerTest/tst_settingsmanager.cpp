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
    void hasKey_correctReturnValue();
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

    QRegExp hexColorRegex("^\\#[0-9ABCDEFabcdef]{6}$");

    qDebug() << settings.getValue("style","nodes-color").toString();

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

void SettingsManagerTest::hasKey_correctReturnValue() {
    //delete previous file
    QFile::remove("config.ini");

    QFile file("config.ini");
    file.open((QIODevice::ReadWrite));
    file.close();

    //if no exception is thrown means that filename is correct
    SettingsManager settings("config.ini");

    QVERIFY( settings.hasKey("style", "preset" ) == true );
    QVERIFY( settings.hasKey("style", "unknown-attr" ) == false );
    QVERIFY( settings.hasKey("unknown-scope", "preset" ) == false );

}



QTEST_MAIN(SettingsManagerTest)
#include "tst_settingsmanager.moc"
