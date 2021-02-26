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

#include "graph.h"


Graph::Graph(QObject* parent ) : QGraphicsScene( parent )
{

}

void Graph::addNode(Node* node)
{

    QVectorIterator<Node*> i(nodes);
    while( i.hasNext() ) {
        if( i.next() == node ) {
            throw GraphError( GraphError::DUPLICATED_NODE, "node duplicated" );
        }
    }

    nodes.push_back(node);
    this->addItem( node );
}

void Graph::addNode(QString name, qreal x, qreal y )
{
    Node* node = new Node( name, x, y );

    this->addNode( node );

}

void Graph::addEdge( QString nameA, QString nameB, int weight ) {
    Node* nodeA = new Node( nameA );
    Node* nodeB = new Node( nameB );
    addEdge( new Edge( nodeA, nodeB, weight ) );
}

void Graph::addEdge( Node* nodeA, Node* nodeB, int weight ) {
    addEdge( new Edge( nodeA, nodeB, weight ) );
}

void Graph::addEdge( Edge* edge ) {
    QVectorIterator<Edge*> i(edges);

    while( i.hasNext() ) {
        if( edge == i.next() )
            throw GraphError( GraphError::DUPLICATED_NODE, "Duplicated edge" );
    }

    edges.push_back( edge );
    this->addItem( edge );
}

bool Graph::load( QString filepath ) {

}

bool Graph::save( QString filepath ) {
    QSettings save( filepath, QSettings::IniFormat );
    QVectorIterator<Node*> node(nodes);

    save.beginGroup( "nodes" );
    while( node.hasNext() ) {
        Node* hold = node.next();
        save.setValue( hold->getName(), QString::number( hold->x() ) + " " +
                                        QString::number( hold->y() ) + " " );
    }
}







