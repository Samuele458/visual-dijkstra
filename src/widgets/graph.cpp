#include "graph.h"



Graph::Graph(QObject* parent ) : QGraphicsScene( parent )
{


}

void Graph::addNode(Node* node)
{
    nodes.push_back(node);
    this->addItem( node );
}

void Graph::addNode(QString name, qreal x, qreal y )
{
    Node* node = new Node( name, x, y );

    this->addNode( node );

}







