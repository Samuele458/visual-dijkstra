/*          Visual Dijkstra
 *    Copyright (C) 2021 Samuele Girgenti
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * 	     --  CONTACTS --
 *   Email:      samuele.girgenti458@gmail.com
 *   Github:     https://github.com/Samuele458
 */

#include "dialogs/mainwindow.h"


MainWindow::MainWindow( QWidget* parent ) : QMainWindow(parent) {

    //creating actions
    createActions();

    //window toolbar
    toolbar = new QToolBar("Visual Dijkstra");
    this->addToolBar( toolbar );
    toolbar->addAction( exitAction );
    toolbar->addAction( saveAction );
    toolbar->addAction( saveAsAction );
    toolbar->addAction( openAction );

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
        graph->addEdge( edge1 );
    } catch( Error e ) {
        qDebug() << e.getMessage() << e.getId();
    }



    editorView->setScene( graph );
    editorView->setRenderHint(QPainter::Antialiasing, true );
    editorView->setSceneRect(graph->sceneRect());

    editorView->viewport()->setCursor(Qt::CrossCursor);

    //maximize window
    this->showMaximized();
}

void MainWindow::createActions() {
    exitAction = new QAction( "Exit", this );
    exitAction->setShortcut( QKeySequence::Quit );
    connect( exitAction, SIGNAL(triggered()), this, SLOT(exit_action_slot()) );

    openAction = new QAction( "Open", this );
    connect( openAction, SIGNAL(triggered()), this, SLOT(open_action_slot()) );

    saveAction = new QAction( "Save", this );
    connect( saveAction, SIGNAL(triggered()), this, SLOT(save_action_slot()) );

    saveAsAction = new QAction( "Save as...", this );
    connect( saveAsAction, SIGNAL(triggered()), this, SLOT(save_as_action_slot()) );

}



// ---- Actions ----

void MainWindow::open_action_slot() {
    QString filename = QFileDialog::getOpenFileName( this, "Open file", "", "Config (*.ini);;Others (*.*)", nullptr );

    if( filename != "" ) {
        graph->load( filename );
    }
}

void MainWindow::exit_action_slot() {
    this->close();
}

void MainWindow::save_action_slot() {
    qDebug() << "save";
}

void MainWindow::save_as_action_slot() {
    QString filename = QFileDialog::getSaveFileName( this, "Save as...", "", "Config (*.ini);;Others (*.*)" );

    if( filename != "" ) {
        graph->save( filename );
    }
}
