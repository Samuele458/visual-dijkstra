#include "node.h"

Node::Node()
{
    this->setFlag(QGraphicsItem::ItemIsMovable,true);

}

Node::Node(QString name, qreal x, qreal y, QGraphicsItem* parent ) : QGraphicsItem(parent)
{
    this->name = name;
    this->setFlag(QGraphicsItem::ItemIsMovable,true);
    QBrush brush(Qt::red);
    this->setPos( x, y );

}

QRectF Node::boundingRect() const
{
    return QRectF(0,0,30,30);
}


void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QGraphicsItem::paint( painter, option, widget );
    QRectF rect = boundingRect();

    QBrush brush(Qt::red);

    painter->setBrush( brush );

    QBrush penBrush(Qt::black);
    QPen pen( penBrush, 3 );

    painter->setPen( pen );
    //painter->drawRect(rect);
    painter->drawEllipse(0,0,rect.width(),rect.height());
    painter->drawText(0,0,50,50,0,"Ciao");
}


