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
    tableSplitter =  new QSplitter(Qt::Orientation::Horizontal);


    tableSplitter->addWidget(editorView);
    tableSplitter->addWidget( table );
    //mainLayout->addWidget(editorView);
    //mainLayout->addWidget( table );
    mainWidget->setLayout(mainLayout);

    this->setCentralWidget( tableSplitter );

    //creating test graph
    graph = new Graph( this );
    try {
    node1 = new Node("B",0,0);
    node2 = new Node("A",0,0);
    edge1 = new Edge( node1, node2, 5 );
    graph->addNode(node1);
    graph->addNode(node2);
    graph->addItem( edge1 );
    } catch( GraphError e ) {
        qDebug() << e.getMessage() << e.getId();
    }



    editorView->setScene( graph );
    editorView->setRenderHint(QPainter::Antialiasing, true );
    editorView->setSceneRect(graph->sceneRect());

    //maximize window
    this->showMaximized();
}
