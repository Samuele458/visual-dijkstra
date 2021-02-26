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
        graph->addEdge( edge1 );
    } catch( Error e ) {
        qDebug() << e.getMessage() << e.getId();
    }



    editorView->setScene( graph );
    editorView->setRenderHint(QPainter::Antialiasing, true );
    editorView->setSceneRect(graph->sceneRect());

    //maximize window
    this->showMaximized();
}
