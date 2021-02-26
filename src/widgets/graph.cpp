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
    Node* nodeA = getNode( nameA );
    Node* nodeB = getNode( nameB );

    if( nodeA == nullptr ) {
        throw GraphError( GraphError::UNKNOWN_NODE, "Unknown node" );
    }

    if( nodeB == nullptr ) {
        throw GraphError( GraphError::UNKNOWN_NODE, "Unknown node" );
    }

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

Node* Graph::getNode( QString name ) const {
    QVectorIterator<Node*> i(nodes);

    while( i.hasNext() ) {
        Node* node = i.next();
        if( node->getName() == name ) {
            return node;
        }
    }

    return nullptr;
}

bool Graph::load( QString filepath ) {
    QSettings load( filepath, QSettings::IniFormat );

    //checking if file exists or not
    if( filepath != "" && QFile::exists( filepath ) ) {

        //todo: completare i controlli sugli item inseriti e rimossi
        //removing all items
        edges.clear();
        nodes.clear();
        QList<QGraphicsItem*> items = this->items();
        QListIterator<QGraphicsItem*> items_i(items);
        while( items_i.hasNext() ) {
            this->removeItem( items_i.next() );
        }

        load.beginGroup( "nodes" );
        QStringList nodes = load.allKeys();
        QStringListIterator i(nodes);
        qDebug() << nodes;

        while( i.hasNext() ) {
            QString nodeName = i.next();
            QStringList coordinates = load.value( nodeName ).toString().split(" ");
            //todo: verificare che  le coordinate siano 2
            this->addNode( nodeName,
                           coordinates.at(0).toInt(),
                           coordinates.at(1).toInt());
        }
        load.endGroup();

        load.beginGroup( "edges" );
        QStringList edges = load.childKeys();
        qDebug() << edges;
        QStringListIterator edges_i( edges );
        while( edges_i.hasNext() ) {
            QString current_edges = edges_i.next();
            qDebug() << current_edges.split("-").at(0) << current_edges.split("-").at(1);
            this->addEdge(current_edges.split("-").at(0),
                          current_edges.split("-").at(1),
                          load.value( current_edges ).toInt() );
        }
        load.endGroup();
    }
    return true;
}

bool Graph::save( QString filepath ) {
    QSettings save( filepath, QSettings::IniFormat );
    QVectorIterator<Node*> node(nodes);
    QVectorIterator<Edge*> edge(edges);

    save.beginGroup( "nodes" );
    while( node.hasNext() ) {
        Node* hold = node.next();
        save.setValue( hold->getName(), QString::number( hold->x() ) + " " +
                                        QString::number( hold->y() ) );
    }
    save.endGroup();

    save.beginGroup( "edges" );
    while( edge.hasNext() ) {
        Edge* hold = edge.next();
        save.setValue( hold->getNodeA()->getName() + "-" + hold->getNodeB()->getName(),
                       hold->getWeight() );
    }
    save.endGroup();
    return true;
}







