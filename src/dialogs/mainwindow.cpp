#include "dialogs/mainwindow.h"


MainWindow::MainWindow( QWidget* parent ) : QMainWindow(parent) {
    toolbar = new QToolBar("Visual Dijkstra");

    editorView = new QGraphicsView;

    this->setCentralWidget( editorView );

    this->addToolBar( toolbar );
}
