#include "edge.h"

Edge::Edge( Node* nodeA, Node* nodeB, int weight, QGraphicsItem* parent) :
    QGraphicsItem( parent )
{
    this->nodeA = nodeA;
    this->nodeB = nodeB;
    this->weight = weight;

    //each node must have a reference to this edge
    nodeA->addEdge( this );
    nodeB->addEdge( this );

    //the lines must be behind the nodes (default Z is 0)
    this->setZValue( -1 );
}


QRectF Edge::boundingRect() const {

    //nodeA coordinates
    QPointF centerA(nodeA->x(),nodeA->y());

    //nodeB coordinates
    QPointF centerB(nodeB->x(),nodeB->y());


    //points used to form the rect
    QPointF topLeft;
    QPointF bottomRight;


    //checking which is the min between centerA and centerB
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

    //adding padding to rect
    topLeft.setX(topLeft.x()-70);
    topLeft.setY(topLeft.y()-70);
    bottomRight.setX(bottomRight.x()+70);
    bottomRight.setY(bottomRight.y()+70);

    return QRectF(topLeft,bottomRight);
};


void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    //creating pen, in order to draw line.
    painter->setPen(QPen(Qt::black, 3));

    //drawing line. The center of each nodes is calculated
    painter->drawLine(nodeA->x()+nodeA->boundingRect().width()/2,
                      nodeA->y()+nodeA->boundingRect().height()/2,
                      nodeB->x()+nodeB->boundingRect().width()/2,
                      nodeB->y()+nodeB->boundingRect().height()/2 );

};

