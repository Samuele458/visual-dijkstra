#include "node.h"

Node::Node() : QGraphicsItem()
{
    this->setFlag(QGraphicsItem::ItemIsMovable,true);

}

Node::Node(QString name, qreal x, qreal y) : Node()
{
    this->name = name;
    this->setX(x);
    this->setY(y);
}

QRectF Node::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(Qt::red);
    painter->fillRect(rect,brush);
    painter->drawRect(rect);
}
