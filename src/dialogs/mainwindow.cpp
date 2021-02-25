#include "dialogs/mainwindow.h"


MainWindow::MainWindow( QWidget* parent ) : QMainWindow(parent) {
    toolbar = new QToolBar("Visual Dijkstra");
    this->addToolBar( toolbar );

    editorView = new QGraphicsView;
    graph = new Graph( this );

    node1 = new Node("A",0,0);
    node2 = new Node("B",100,0);
    node3 = new Node("C",100,100);
    graph->addNode(node1);
    graph->addNode(node2);
    graph->addNode(node3);

    edge1 = new Edge(node1, node2, 3);
    graph->addItem(edge1);

    edge2 = new Edge(node2, node3, 3);
    graph->addItem(edge2);

    editorView->setScene( graph );
    this->setCentralWidget( editorView );

    editorView->setRenderHint(QPainter::Antialiasing, true );
    editorView->setSceneRect(graph->sceneRect());
}
