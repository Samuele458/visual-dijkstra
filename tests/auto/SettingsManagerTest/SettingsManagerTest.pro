QT += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11

INCDIR = ../../../src


INCLUDEPATH += $$INCDIR

HEADERS += \
        $$INCDIR/common/error.h \
        $$INCDIR/common/settingsmanager.h



SOURCES += \
        $$INCDIR/common/error.cpp \
        $$INCDIR/common/settingsmanager.cpp

RESOURCES += \
        $$INCDIR/data.qrc

SOURCES += \
        tst_settingsmanager.cpp
