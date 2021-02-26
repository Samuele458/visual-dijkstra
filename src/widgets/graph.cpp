#include "graph.h"



Graph::Graph(QObject* parent ) : QGraphicsScene( parent )
{

}

void Graph::addNode(Node* node)
{

    QVectorIterator<Node*> i(nodes);
    while( i.hasNext() ) {
        if( i.next()->getName() == node->getName() ) {
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

bool Graph::load( QString filepath ) {

}

bool Graph::save( QString filepath ) {

}







