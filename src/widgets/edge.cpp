#include "edge.h"

Edge::Edge( Node* nodeA, Node* nodeB, int weight, QGraphicsItem* parent) :
    QGraphicsItem( parent )
{
    this->nodeA = nodeA;
    this->nodeB = nodeB;
    this->weight = weight;

    nodeA->addEdge( this );
    nodeB->addEdge( this );

    this->setZValue( -1 );
}


QRectF Edge::boundingRect() const {

    QPointF centerA(nodeA->x(),nodeA->y());
    QPointF centerB(nodeB->x(),nodeB->y());
    QPointF topLeft;
    QPointF bottomRight;



    if( centerA.x() > centerB.x() ) {
        topLeft.setX( centerB.x() );
        bottomRight.setX( centerA.x() );
    } else {
        topLeft.setX( centerA.x() );
        bottomRight.setX( centerB.x() );
    }

    if( centerA.y() > centerB.y() ) {
        topLeft.setY( centerB.y() );
        bottomRight.setY( centerA.y() );
    } else {
        topLeft.setY( centerA.y() );
        bottomRight.setY( centerB.y() );
    }

    topLeft.setX(topLeft.x()-70);
    topLeft.setY(topLeft.y()-70);
    bottomRight.setX(bottomRight.x()+70);
    bottomRight.setY(bottomRight.y()+70);

    //nodeA->boundingRect().width()/2;

    return QRectF(topLeft,bottomRight);
};


void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    //QBrush brush(Qt::black);
    //painter->setBrush( brush );
    //painter->drawRect( boundingRect() );
    qDebug() << nodeA->x()<<nodeA->y()<<nodeB->x()<<nodeB->y();

    painter->setPen(QPen(Qt::black, 3));
    painter->drawLine(nodeA->x()+nodeA->boundingRect().width()/2,
                      nodeA->y()+nodeA->boundingRect().height()/2,
                      nodeB->x()+nodeB->boundingRect().width()/2,
                      nodeB->y()+nodeB->boundingRect().height()/2 );

    qDebug() << nodeA->x();
};

