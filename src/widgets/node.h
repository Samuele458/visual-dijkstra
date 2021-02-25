#ifndef NODE_H
#define NODE_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

class Node : public QGraphicsItem
{
public:
    Node();
    Node( QString name, qreal x = 0, qreal y = 0, QGraphicsItem* parent = nullptr );

    QRectF boundingRect() const;
    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );

private:
    QString name;
};

#endif // NODE_H
