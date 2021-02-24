#include <QApplication>
#include "dialogs/mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow dijkstraWindow;

    dijkstraWindow.show();
    return a.exec();
}
