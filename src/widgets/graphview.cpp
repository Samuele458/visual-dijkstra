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

#include "graphview.h"

GraphView::GraphView(Graph* graph, QWidget* parent ) :
    QGraphicsView( parent ), graph( graph )
{
    this->setScene( graph );
    this->setRenderHint(QPainter::Antialiasing, true );
    this->setMouseTracking( true );

    graph->setSceneRect(-10000,-10000,20000,20000);

    //setDragMode(ScrollHandDrag);
    //setDragMode(DragMode::)
    this->viewport()->setCursor(Qt::CrossCursor);
}


GraphView::GraphView( QWidget* parent ) :
    GraphView( new Graph(), parent )
{

}

Graph* GraphView::getGraph() const {
    return this->graph;
}

void GraphView::setGraph( Graph* graph ) {
    this->graph = graph;
}

void GraphView::wheelEvent(QWheelEvent *event) {
    if( event->angleDelta().y() > 0 ) {
    qDebug() << QTime::currentTime().toString() << "Zoomin";

        this->scale( 1.1, 1.1 );
    } else {
        qDebug() << "zoomout";
        this->scale( 0.9, 0.9 );
    }

    if( event->modifiers().testFlag(Qt::ControlModifier) ) {
        qDebug() << "ctrl";
    }
}

void GraphView::keyPressEvent(QKeyEvent *event) {
    if( event->key() == Qt::Key_Space && !event->isAutoRepeat() ) {
        qDebug() << "Space pressed";
        setDragMode(DragMode::ScrollHandDrag);
    }
}

void GraphView::keyReleaseEvent(QKeyEvent *event) {
    if( event->key() == Qt::Key_Space && !event->isAutoRepeat() ) {
        qDebug() << "Space unpressed";
        setDragMode(DragMode::NoDrag);
    }
}
