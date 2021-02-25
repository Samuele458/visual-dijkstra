#include "dialogs/mainwindow.h"


MainWindow::MainWindow( QWidget* parent ) : QMainWindow(parent) {

    //window toolbar
    toolbar = new QToolBar("Visual Dijkstra");
    this->addToolBar( toolbar );

    //setup UI
    editorView = new QGraphicsView;
    mainWidget =  new QWidget;
    mainLayout = new QHBoxLayout;
    table = new QTableWidget;

    mainLayout->addWidget(editorView);
    mainLayout->addWidget( table );
    mainWidget->setLayout(mainLayout);

    this->setCentralWidget( mainWidget );

    //creating test graph
    graph = new Graph( this );
    node1 = new Node("A",0,0);
    graph->addNode(node1);
    editorView->setScene( graph );
    editorView->setRenderHint(QPainter::Antialiasing, true );
    editorView->setSceneRect(graph->sceneRect());

    //maximize window
    this->showMaximized();
}
