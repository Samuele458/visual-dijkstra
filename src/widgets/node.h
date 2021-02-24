#ifndef NODE_H
#define NODE_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

class Node : public QGraphicsItem
{
public:
    Node();

    QRectF boundingRect() const;
    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );


};

#endif // NODE_H
