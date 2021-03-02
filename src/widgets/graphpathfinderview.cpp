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

#include "graphpathfinderview.h"

GraphPathfinderView::GraphPathfinderView( Graph* graph, QWidget* parent ) :
    GraphView( graph, parent )
{
    pathCalculationRequested = false;
    pathCalculationHold = nullptr;

    statesWidget = nullptr;
}


GraphPathfinderView::GraphPathfinderView( QWidget* parent ) :
    GraphView( parent )
{
    pathCalculationRequested = false;
    pathCalculationHold = nullptr;

    statesWidget = nullptr;
}

void GraphPathfinderView::requestUserAction( Action action ) {
    pathCalculationRequested = false;
    pathCalculationHold = nullptr;

    switch( action ) {
        case CALCULATE_PATH:
            pathCalculationRequested = true;
            break;
    }
}

void GraphPathfinderView::mousePressEvent(QMouseEvent *event) {
    GraphView::mousePressEvent( event );

    //getting mouse coordinates
    //int x = event->pos().x();
    //int y = event->pos().y();

    //checking for Path Calculation request
    if( pathCalculationRequested ) {
        //Path Calculation request allows user to calculate
        //path between two nodes
        QGraphicsItem *item = itemAt(event->pos());
        Node* node = qgraphicsitem_cast<Node*>(item);
        if( node != NULL ) {

            //because of the nodes to be linked are two, the first one will
            //be stored into pathCalculationHold. If it is equal to nullptr, it
            //means that the first node has not been selected yet.
            if( pathCalculationHold == nullptr ) {
                //storing first node
                pathCalculationHold = node;
            } else {
                //if pathCalculationHold != nullptr means that first node has already
                //stored, so the calculation will be done
                qDebug() << pathCalculationHold->getName() << "->" << node->getName();
                QVector<GraphState> states = dijkstraAlgorithm( pathCalculationHold );
                if( statesWidget != nullptr ) {
                    statesWidget->clearStates();
                    statesWidget->setStates( states );
                }

                pathCalculationHold = nullptr;
                pathCalculationRequested = false;
            }
        } else {
            //if item is not a Node*, procedure will be terminated
            pathCalculationHold = nullptr;
            pathCalculationRequested = false;
        }
    }
}

QVector<GraphState> GraphPathfinderView::dijkstraAlgorithm( Node* source ) {

    QVector<GraphState> states;

    //initializing graph state
    GraphState state( this->getGraph() );

    //source node must have 0 distance
    state.setDistance( source->getName(), 0 );

    //QStringList nodesList = state.getNodeNames();
    QVectorIterator<Node*> i(this->getGraph()->getNodes());


    states.push_back( state );
    qDebug().noquote() << state.toString();

    //while nodesList is not empty
    while( i.hasNext() ) {
        Node* node = i.next();


        Node* u = this->getGraph()->getNode( state.minDistance() );

        qDebug() << "New node: " + u->getName();
        qDebug().noquote() << state.toString();

        //current node set processed
        state.setProcessed( u->getName(), true );

        QVector<Node*> neighbours( u->getNeighbours() );
        for( int j = 0; j < neighbours.size(); ++j ) {
            int alt = state.getNode(u->getName()).getDistance() +
                      u->getEdgeBetween( neighbours.at(j) )->getWeight();
            qDebug() << "neighbour:  " +neighbours.at(j)->getName() + "  - " + QString::number(alt) + " - " + QString::number(state.getNode(neighbours.at(j)->getName()).getDistance() );
            if( alt < state.getNode(neighbours.at(j)->getName()).getDistance() ) {
                state.setDistance( neighbours.at(j)->getName(), alt );
                state.setPreviousNodeName( neighbours.at(j)->getName(), u->getName() );
            }

        }
        states.push_back( state );
    }

    qDebug().noquote() << state.toString();


    return states;

}

void GraphPathfinderView::setStatesWidget( GraphStatesWidget* widget ) {
    this->statesWidget = widget;
}

GraphStatesWidget* GraphPathfinderView::getStatesWidget() const {
    return statesWidget;
}





