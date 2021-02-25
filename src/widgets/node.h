#ifndef NODE_H
#define NODE_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include "widgets/edge.h"


class Edge;


class Node : public QGraphicsItem
{
public:
    Node();
    Node( QString name, qreal x = 0, qreal y = 0, QGraphicsItem* parent = nullptr );

    QRectF boundingRect() const;
    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void addEdge( Edge* edge );
private:
    QString name;
    QVector<Edge*> edges;
};

#endif // NODE_H
