#ifndef EDGE_H
#define EDGE_H
#include <QGraphicsItem>
#include <QStyle>
#include "widgets/node.h"

class Node;

class Edge : public QGraphicsItem
{
public:
    Edge( Node* nodeA, Node* nodeB, int weight, QGraphicsItem* parent = nullptr );


protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private:
    int weight;
    Node* nodeA;
    Node* nodeB;

};

#endif // EDGE_H
