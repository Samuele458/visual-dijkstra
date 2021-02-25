#include "dialogs/mainwindow.h"


MainWindow::MainWindow( QWidget* parent ) : QMainWindow(parent) {
    toolbar = new QToolBar("Visual Dijkstra");

    editorView = new QGraphicsView;
    graph = new Graph( this );
    //scene = new QGraphicsScene(this);
    graph->addNode("test",0,0);
    editorView->setScene( graph );

    //QGraphicsEllipseItem()
    //node = new Node();
    //scene->addItem( node );
    //scene->addRect(-100,-30,50,50);
    //scene->addLine(0,100,200,300);

    //scene->addRect()

    this->setCentralWidget( editorView );

    this->addToolBar( toolbar );

    graph->addNode("test",300,300);

    editorView->setRenderHint(QPainter::Antialiasing, true );

}
