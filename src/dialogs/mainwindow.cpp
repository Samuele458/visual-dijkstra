#include "dialogs/mainwindow.h"


MainWindow::MainWindow( QWidget* parent ) : QMainWindow(parent) {
    toolbar = new QToolBar("Visual Dijkstra");

    editorView = new QGraphicsView;

    scene = new QGraphicsScene(this);
    editorView->setScene( scene );
    node = new Node();
    scene->addItem( node );
    scene->addRect(-100,-30,50,50);
    scene->addLine(0,100,200,300);

    this->setCentralWidget( editorView );

    this->addToolBar( toolbar );
}
