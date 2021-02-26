#ifndef EDGE_H
#define EDGE_H
#include <QGraphicsItem>
#include <QStyle>
#include "widgets/node.h"

class EdgeError : public Error {
public:
    enum id {
        GENERIC,
        INVALID_ARGUMENT,

        INVALID_NODES
    };

    EdgeError( id error_id = GENERIC, QString message = "" ) :
        Error( (Error::id)error_id, message ) { }
};

class Node;

class Edge : public QGraphicsItem
{
public:
    Edge( Node* nodeA, Node* nodeB, int weight, QGraphicsItem* parent = nullptr );

    bool operator==( Edge& other );
    bool operator!=( Edge& other );

    Node* getNodeA() const;
    Node* getNodeB() const;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private:
    int weight;
    Node* nodeA;
    Node* nodeB;

};

#endif // EDGE_H
