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


//default color for lines, and nodes borders
const QColor Graph::DEFAULT_LINE_COLOR = Qt::black;

//default background color for nodes
const QColor Graph::DEFAULT_ITEM_COLOR = Qt::white;

//highlighted color for lines, and nodes borders
const QColor Graph::HIGHLIGHT_LINE_COLOR = Qt::blue;

//highlighted background color for nodes
const QColor Graph::HIGHLIGHT_ITEM_COLOR = Qt::green;

//Path color for nodes
const QColor Graph::PATH_ITEM_COLOR = Qt::red;

//line color for nodes and edges
const QColor Graph::PATH_LINE_COLOR = Qt::red;


Graph::Graph(QObject* parent ) : QGraphicsScene( parent )
{

    nodeRemovalRequested = false;
    nodeCreationRequested = false;
    edgeCreationRequested = false;
    edgeCreationHold = nullptr;


    //item removing causing SIGSEGV bug solved
    this->setItemIndexMethod(QGraphicsScene::ItemIndexMethod::NoIndex);

    //set graph not saved
    saved = true;

}

void Graph::addNode(Node* node)
{

    QVectorIterator<Node*> i(nodes);
    while( i.hasNext() ) {
        Node* hold = i.next();
        if( *hold == *node || hold == node  ) {
            throw GraphError( GraphError::DUPLICATED_NODE, "node duplicated" );
        }
    }

    nodes.push_back(node);
    this->addItem( node );

    //set graph not saved
    saved = false;

    update();
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

    //set graph not saved
    saved = false;

    update();
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

QVector<Node*> Graph::getNodes() const {
    return nodes;
}

void Graph::highlightState(GraphState state , bool drawPath) {
    QVector<NodeState> states = state.getNodes();

    //resetting nodes
    for( int i = 0; i < nodes.size(); ++i ) {
        nodes.at(i)->setBorderColor( DEFAULT_LINE_COLOR );
    }

    //resetting edges
    for( int i = 0; i < edges.size(); ++i ) {
        edges.at(i)->setColor( DEFAULT_LINE_COLOR );
    }

    //apply new styles
    for( int i = 0; i < states.size(); ++i ) {
        if( states.at(i).getPreviousNodeName() != "" ) {
            getNode( states.at(i).getName() )->setBorderColor(Graph::HIGHLIGHT_LINE_COLOR);
            getNode( states.at(i).getName() )->getEdgeBetween( getNode(states.at(i).getPreviousNodeName()))
                    ->setColor( HIGHLIGHT_LINE_COLOR );
        }
    }

    getNode( state.getSource() )->setBorderColor(Graph::PATH_LINE_COLOR);
    getNode( state.getDest() )->setBorderColor(Graph::PATH_LINE_COLOR);

    if( drawPath ) {
        NodeState node = state.getNode(state.getDest());
        QVector<NodeState> pathNodes;
        pathNodes.push_back( node );

        while( node.getPreviousNodeName() != "" ) {

            node = state.getNode(node.getPreviousNodeName());
            pathNodes.push_back( node );
        }

        if( pathNodes.size() >= 2 && pathNodes.at(0).getName() == state.getDest() &&
            pathNodes.at(pathNodes.size()-1).getName() == state.getSource() ) {
            for( int i = 0; i < pathNodes.size()-1; ++i ) {
                getNode( pathNodes.at(i).getName() )
                        ->getEdgeBetween( getNode(pathNodes.at(i+1).getName()) )
                        ->setColor(PATH_LINE_COLOR);
                getNode( pathNodes.at(i).getName() )->setBorderColor( PATH_LINE_COLOR );

            }
        }

    }

    //updating Scene
    update(-10000,-10000,20000,20000);
}

void Graph::resetState() {
    QVectorIterator<Node*> i(nodes);

    while( i.hasNext() ) {
        Node* node = i.next();
        node->setBackgroundColor( Graph::DEFAULT_ITEM_COLOR );
        node->setBorderColor( Graph::DEFAULT_LINE_COLOR );
    }


    QVectorIterator<Edge*> j(edges);

    while( j.hasNext() ) {
        j.next()->setColor( DEFAULT_LINE_COLOR );
    }

    this->update();
}




void Graph::removeEdge( QString nameA, QString nameB ) {
    QVectorIterator<Edge*> i(edges);

    while( i.hasNext() ) {
        Edge* hold = i.next();

        if( ( hold->getNodeA()->getName() == nameA && hold->getNodeB()->getName() == nameB ) ||
            ( hold->getNodeA()->getName() == nameB && hold->getNodeB()->getName() == nameA ) ) {
            removeEdge( hold );

            //set graph not saved
            saved = false;
        }
    }
}

void Graph::removeEdge( Node* nodeA, Node* nodeB ) {
    QVectorIterator<Edge*> i(edges);

    while( i.hasNext() ) {
        Edge* hold = i.next();

        if( ( hold->getNodeA() == nodeA && hold->getNodeB() == nodeB ) ||
            ( hold->getNodeA() == nodeB && hold->getNodeB() == nodeA ) ) {
            removeEdge( hold );

            //set graph not saved
            saved = false;
        }
    }
}

void Graph::removeEdge( Edge* edge ) {
    for( int i = 0; i < edges.size(); ++i ) {
        if( edges.at(i) == edge ) {

            edges.at(i)->getNodeA()->removeEdge( edge );
            edges.at(i)->getNodeB()->removeEdge( edge );
            removeItem( edge );
            edges.removeAt( i );

            delete edge;

            //set graph not saved
            saved = false;

        }
    }
}

void Graph::removeNode( QString name ) {
    QVectorIterator<Node*> i(nodes);

    while( i.hasNext() ) {
        Node* hold = i.next();
        if( hold->getName() == name ) {
            removeNode( hold );

            //set graph not saved
            saved = false;

            return;
        }
    }
}

void Graph::removeNode( Node* node ) {
    for( int i = 0; i < nodes.size(); ++i ) {
        if( node == nodes.at(i) ) {

            QVectorIterator<Edge*> edge_i( node->getEdges() );
            while( edge_i.hasNext() ) {
                Edge* hold = edge_i.next();

                removeEdge( hold );
            }

            removeItem( node );
            nodes.removeAt(i);
            delete node;


            //set graph not saved
            saved = false;

        }
    }
}


bool Graph::load( QString filepath ) {
    //reset any pending request
    resetRequest();

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

        while( i.hasNext() ) {
            QString nodeName = i.next();
            QStringList coordinates = load.value( nodeName ).toString().split(" ");
            //todo: check coordinates
            this->addNode( nodeName,
                           coordinates.at(0).toInt(),
                           coordinates.at(1).toInt());
        }
        load.endGroup();

        load.beginGroup( "edges" );
        QStringList edges = load.childKeys();
        QStringListIterator edges_i( edges );
        while( edges_i.hasNext() ) {
            QString current_edges = edges_i.next();
            this->addEdge(current_edges.split("-").at(0),
                          current_edges.split("-").at(1),
                          load.value( current_edges ).toInt() );
        }
        load.endGroup();

        //set graph saved
        saved = true;
    }
    return true;
}

bool Graph::save( QString filepath ) {

    //reset any pending request
    resetRequest();

    QFile file(filepath);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate)) {
        return false;
    }
    file.close();


    QSettings save( filepath, QSettings::IniFormat );
    QVectorIterator<Node*> node(nodes);
    QVectorIterator<Edge*> edge(edges);

    save.beginGroup( "nodes" );
    while( node.hasNext() ) {
        Node* hold = node.next();
        save.setValue( hold->getName(), QString::number( (int)hold->x() ) + " " +
                                        QString::number( (int)hold->y() ) );
    }
    save.endGroup();

    save.beginGroup( "edges" );
    while( edge.hasNext() ) {
        Edge* hold = edge.next();
        save.setValue( hold->getNodeA()->getName() + "-" + hold->getNodeB()->getName(),
                       hold->getWeight() );
    }
    save.endGroup();

    //set graph saved
    saved = true;

    return true;
}

void Graph::emptyGraph() {
    //todo: completare i controlli sugli item inseriti e rimossi
    //removing all items
    edges.clear();
    nodes.clear();
    QList<QGraphicsItem*> items = this->items();
    QListIterator<QGraphicsItem*> items_i(items);
    while( items_i.hasNext() ) {
        this->removeItem( items_i.next() );
    }

    saved = true;
}

void Graph::requestUserAction( Action action ) {

    //resetting all flags
    nodeRemovalRequested = false;
    nodeCreationRequested = false;
    edgeCreationRequested = false;
    edgeCreationHold = nullptr;

    switch (action) {
        case CREATE_NODE:
            nodeCreationRequested = true;
            break;
        case REMOVE_NODE:
            nodeRemovalRequested = true;
            break;
        case CREATE_EDGE:
            edgeCreationRequested = true;
            break;
    }
}

void Graph::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent( event );

    //getting mouse coordinates
    int x = event->buttonDownScenePos(Qt::LeftButton).x();
    int y = event->buttonDownScenePos(Qt::LeftButton).y();

    //checking for Node Creation request
    if( nodeCreationRequested ) {
        bool ok;

        //asking node name
        QString nodeName = QInputDialog::getText(nullptr, "new node",
                                                 "Node name:", QLineEdit::Normal,
                                                 "", &ok, Qt::MSWindowsFixedSizeDialogHint );
        //if form was confirmed
        if( ok ) {
            try {

                //trying to add node
                this->addNode(nodeName, x, y);

            }  catch ( Error e ) {
                QMessageBox::warning( nullptr, "Warning", e.getMessage() );
            }
        }

        //reset the request flag
        nodeCreationRequested = false;
    }

    //checking for Node Remuval request
    if( nodeRemovalRequested ) {

        //item selected by mouse
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());

        //casting into a node
        Node* node = qgraphicsitem_cast<Node*>(item);

        //checking if item is a node or other item (like edge, etc)
        //qgraphicsitem_cast return NULL if node isn't Node*
        if( node != NULL ) {
            removeNode( node );
        }


        //reset flag
        nodeRemovalRequested = false;
    }


    //checking for Edge Creation request
    if( edgeCreationRequested ) {

        //Edge Creation request allows user to create
        //edges between two nodes by clicking them

        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        Node* node = qgraphicsitem_cast<Node*>(item);
        if( node != NULL ) {

            //because of the nodes to be linked are two, the first one will
            //be stored into edgeCreationHold. If it is equal to nullptr, it
            //means that the first node has not been selected yet.
            if( edgeCreationHold == nullptr ) {
                //storing first node
                edgeCreationHold = node;
            } else {
                //if edgeCreationHold != nullptr means that first node has already
                //stored, so edge can be created
                this->addEdge( edgeCreationHold, node );
                edgeCreationHold = nullptr;
                edgeCreationRequested = false;
            }
        } else {
            //if item is not a Node*, procedure will be terminated
            edgeCreationHold = nullptr;
            edgeCreationRequested = false;
        }
    }

    //set graph not saved
    saved = false;
}

void Graph::resetRequest() {
    nodeRemovalRequested = false;
    nodeCreationRequested = false;
    edgeCreationRequested = false;
    edgeCreationHold = nullptr;
}

QString Graph::toString() {
    QString string = "";

    string += "------------------\n";
    string += "Nodes: " + QString::number(nodes.size()) + "\n";
    string += "Edges: " + QString::number(edges.size()) + "\n";
    string += "Total items: " + QString::number(items().size()) + "\n";
    string += "Nodes dump:\n";
    for( int i = 0; i < nodes.size(); ++i ) {
        string += "  - " + nodes.at(i)->toString();
    }
    string += "Edges dump:\n";
    for( int i = 0; i < edges.size(); ++i ) {
        string += "  - " + edges.at(i)->toString() + "\n";
    }

    return string;
}

bool Graph::isSaved() {
    return this->saved;
}







