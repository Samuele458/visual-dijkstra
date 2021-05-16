QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        common/error.cpp \
        common/graphstate.cpp \
        common/settingsmanager.cpp \
        common/adjacencymatrix.cpp \
        dialogs/aboutdialog.cpp \
        dialogs/licensedialog.cpp \
        dialogs/mainwindow.cpp \
        dialogs/settingsdialog.cpp \
        dialogs/matrixdialog.cpp \
        main.cpp \
        widgets/edge.cpp \
        widgets/graph.cpp \
        widgets/graphpathfinderview.cpp \
        widgets/graphstatestable.cpp \
        widgets/graphstateswidget.cpp \
        widgets/graphview.cpp \
        widgets/node.cpp \
        widgets/settingspage.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    common/error.h \
    common/graphstate.h \
    common/settingsmanager.h \
    common/adjacencymatrix.h \
    dialogs/aboutdialog.h \
    dialogs/licensedialog.h \
    dialogs/mainwindow.h \
    dialogs/settingsdialog.h \
    dialogs/matrixdialog.h \
    widgets/edge.h \
    widgets/graph.h \
    widgets/graphpathfinderview.h \
    widgets/graphstatestable.h \
    widgets/graphstateswidget.h \
    widgets/graphview.h \
    widgets/node.h \
    widgets/settingspage.h

RESOURCES += \
    data.qrc

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

#app icon
RC_ICONS = data/icons/logo.ico

DISTFILES +=
