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

#include "graphstate.h"


const int NodeState::INF = 9999999;


NodeState::NodeState( QString name, int distance, QString previous, bool processed ) {
    this->name = name;
    this->distance = distance;
    this->previous = previous;
    this->processed = processed;
}

NodeState::NodeState( const NodeState& other ) {
    name = other.name;
    distance = other.distance;
    previous = other.previous;
    processed = other.processed;
}

NodeState::NodeState( Node* node, int distance, QString previous, bool processed ) :
    NodeState( node->getName(), distance, previous, processed )
{

}

NodeState& NodeState::operator=( const NodeState& other ) {
    name = other.name;
    distance = other.distance;
    previous = other.previous;
    processed = other.processed;

    return *this;
}

bool NodeState::operator==( const NodeState& other ) {
    return distance == other.distance;
}

bool NodeState::operator!=( const NodeState& other ) {
    return !operator==( other );
}

bool NodeState::operator>( const NodeState& other ) {
    return distance > other.distance;
}

bool NodeState::operator<( const NodeState& other ) {
    return distance < other.distance;
}

bool NodeState::operator>=( const NodeState& other ) {
    return distance >= other.distance;
}

bool NodeState::operator<=( const NodeState& other ) {
    return distance <= other.distance;
}

QString NodeState::getName() const {
    return this->name;
}

int NodeState::getDistance() const {
    return this->distance;
}

QString NodeState::getPreviousNodeName() const {
    return this->previous;
}

bool NodeState::isProcessed() const {
    return processed;
}

void NodeState::setName( QString name ) {

    //name could not be empty
    if( name == "" ) {
        throw GraphStateError( GraphStateError::INVALID_NODE_NAME );
    } else {
        this->name = name;
    }
}

void NodeState::setDistance( int distance ) {
    //only distance > 0 or equal to INF is allowed
    if( distance != INF && distance < 0 ) {
        throw GraphStateError( GraphStateError::INVALID_NODE_DISTANCE );
    } else {
        this->distance = distance;
    }
}

void NodeState::setPreviousNodeName( QString previous ) {
    this->previous = previous;
}

void NodeState::setProcessed( bool processed ) {
    this->processed = processed;
}

QString NodeState::toString() const {

    return "Node name: " + name +
           "  Distance:" + QString::number( distance ) +
           "  Previous: " + previous +
           "  Processed: " + ( processed ? "True" : "False") + "\n";

}



// -----

GraphState::GraphState( Graph* graph ) {
    QVector<Node*> nodes = graph->getNodes();
    QVectorIterator<Node*> i(nodes);

    while( i.hasNext() ) {
        Node* hold = i.next();

        this->nodes.push_back( NodeState( hold->getName() ) );
    }

    source = "";
    dest = "";
}

GraphState::GraphState( QVector<NodeState> nodes ) :
    nodes( nodes )
{
    source = "";
    dest = "";
}

GraphState::GraphState( const GraphState& other ) {
    nodes = other.nodes;
    source = other.source;
    dest = other.dest;
}

GraphState& GraphState::operator=( const GraphState& other ) {
    nodes = other.nodes;
    source = other.source;
    dest = other.dest;

    return *this;
}

QVector<NodeState> GraphState::getNodes() const {
    return nodes;
}

void GraphState::setNodes( QVector<NodeState> nodes ) {
    QStringList hold_names;

    this->nodes.clear();

    QVectorIterator<NodeState> i(nodes);
    while( i.hasNext() ) {
        NodeState node = i.next();
        QString name = node.getName();
        if( hold_names.indexOf( name ) != -1 ) {
            throw GraphStateError( GraphStateError::DUPLICATE_NODE_NAME, "Name duplicate" );
        } else {
            hold_names.push_back( name );
            this->nodes.push_back(node);
        }
    }
}

void GraphState::setDistance( QString nodeName, int distance ) {

    for( int i = 0; i < nodes.size(); ++i ) {

        if( nodes.at(i).getName() == nodeName ) {
            NodeState node = nodes.at(i);
            node.setDistance( distance );
            nodes.replace( i, node );
        }
    }

}

void GraphState::setPreviousNodeName( QString nodeName, QString previous ) {

    for( int i = 0; i < nodes.size(); ++i ) {

        if( nodes.at(i).getName() == nodeName ) {
            NodeState node = nodes.at(i);
            node.setPreviousNodeName( previous );
            nodes.replace( i, node );
        }
    }

}

void GraphState::setProcessed( QString nodeName, bool processed ) {

    for( int i = 0; i < nodes.size(); ++i ) {

        if( nodes.at(i).getName() == nodeName ) {
            NodeState node = nodes.at(i);
            node.setProcessed( processed );
            nodes.replace( i, node );
        }
    }

}

bool GraphState::hasInfinity() const {
    QVectorIterator<NodeState> i(nodes);
    while( i.hasNext() ) {
        NodeState node = i.next();

        if( node.getDistance() == NodeState::INF ) {
            return true;
        }
    }

    return false;
}

NodeState GraphState::getNode( QString nodeName ) const {
    QVectorIterator<NodeState> i(nodes);
    while( i.hasNext() ) {
        NodeState node = i.next();

        if( node.getName() == nodeName ) {
            return node;
        }
    }
    throw GraphStateError( GraphStateError::NODE_NOT_FOUND, "Node not found");
    //todo: return
}

QStringList GraphState::getNodeNames() const {
    QStringList names;

    QVectorIterator<NodeState> i(nodes);
    while( i.hasNext() ) {
        names.push_back( i.next().getName() );
    }

    return names;
}

QString GraphState::minDistance() const {

    QVectorIterator<NodeState> i(nodes);
    QVector<NodeState> notProcessed;

    while( i.hasNext() ) {
        NodeState node = i.next();

        if( !node.isProcessed() )
            notProcessed.push_back( node );
    }

    if( notProcessed.size() > 0 ) {
        int min = 0;

        for( int i = 0; i < notProcessed.size(); ++i ) {
            if( notProcessed.at(i).getDistance() < notProcessed.at(min).getDistance() ) {
                min = i;
            }
        }

        return notProcessed.at(min).getName();
    } else {
        return "";
    }
}

QString GraphState::toString() const {
    QString string = "";

    string += "------------------\n";
    string += "Nodes: " + QString::number( nodes.size() ) + "\n";

    QVectorIterator<NodeState> i(nodes);
    while( i.hasNext() ) {
        string += i.next().toString();
    }

    return string;
}

QString GraphState::getSource() const {
    return source;
}

QString GraphState::getDest() const {
    return dest;
}

void GraphState::setSource( QString source ) {
    this->source = source;
}

void GraphState::setDest( QString dest ) {
    this->dest = dest;
}



