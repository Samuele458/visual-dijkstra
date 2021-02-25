#include "node.h"

Node::Node(QString name, qreal x, qreal y, QGraphicsItem* parent ) : QGraphicsItem(parent)
{
    this->name = name;

    this->setFlag(QGraphicsItem::ItemIsMovable,true);

    //item position
    this->setPos( x, y );
}

QRectF Node::boundingRect() const
{
    return QRectF(0,0,30,30);
}


void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //item area
    QRectF bound = boundingRect();

    //brush for item background
    QBrush brush(Qt::red);

    //bruch for contours
    QBrush contourBrush(Qt::black);
    QPen pen( contourBrush, 3 );

    painter->setBrush( brush );
    painter->setPen( pen );

    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont( font );


    //painter->drawRect(rect);
    painter->drawEllipse(0,0,bound.width(),bound.height());
    painter->drawText(0,0,bound.width(),bound.height(),Qt::AlignCenter,name);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //refreshing each edge
    QVectorIterator<Edge*> i(edges);
    while(i.hasNext())
        i.next()->update();

    QGraphicsItem::mouseMoveEvent( event );
}

void Node::addEdge(Edge* edge)
{
    edges.push_back(edge);
}


