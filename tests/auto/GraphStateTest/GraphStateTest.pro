QT += core gui widgets testlib

CONFIG += c++11

INCDIR = ../../../src


INCLUDEPATH += $$INCDIR

HEADERS += \
        $$INCDIR/common/graphstate.h \
        $$INCDIR/common/error.h \
        $$INCDIR/widgets/node.h \
        $$INCDIR/widgets/edge.h \
        $$INCDIR/widgets/graph.h

SOURCES += \
        $$INCDIR/common/graphstate.cpp \
        $$INCDIR/common/error.cpp \
        $$INCDIR/widgets/node.cpp \
        $$INCDIR/widgets/edge.cpp \
        $$INCDIR/widgets/graph.cpp

RESOURCES += \
        $$INCDIR/data.qrc

SOURCES += tst_nodestate.cpp
