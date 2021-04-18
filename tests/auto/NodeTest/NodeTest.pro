QT += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11

INCDIR = ../../../src


INCLUDEPATH += $$INCDIR

HEADERS += \
        $$INCDIR/common/graphstate.h \
        $$INCDIR/common/error.h \
        $$INCDIR/widgets/node.h \
        $$INCDIR/widgets/edge.h \
        $$INCDIR/widgets/graph.h \
        $$INCDIR/widgets/graphview.h


SOURCES += \
        $$INCDIR/common/graphstate.cpp \
        $$INCDIR/common/error.cpp \
        $$INCDIR/widgets/node.cpp \
        $$INCDIR/widgets/edge.cpp \
        $$INCDIR/widgets/graph.cpp \
        $$INCDIR/widgets/graphview.cpp


SOURCES += \
        tst_node.cpp
