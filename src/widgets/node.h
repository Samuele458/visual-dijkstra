#ifndef NODE_H
#define NODE_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

class Node : public QGraphicsEllipseItem
{
public:
    Node();
    Node( QString name, qreal x, qreal y );

    QRectF boundingRect() const;
    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );

private:
    QString name;
};

#endif // NODE_H
