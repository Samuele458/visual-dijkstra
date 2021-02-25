#include "edge.h"

Edge::Edge( Node* nodeA, Node* nodeB, int weight, QGraphicsItem* parent) :
    QGraphicsItem( parent )
{
    this->nodeA = nodeA;
    this->nodeB = nodeB;
    this->weight = weight;

    nodeA->addEdge( this );
    nodeB->addEdge( this );
}


QRectF Edge::boundingRect() const {
    return QRectF(0,0,50,50);
};


void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    //QBrush brush(Qt::black);
    //painter->setBrush( brush );
    painter->drawRect( boundingRect() );
    qDebug() << nodeA->x()<<nodeA->y()<<nodeB->x()<<nodeB->y();
    painter->drawLine(nodeA->x(),nodeA->y(),nodeB->x(),nodeB->y());


};

