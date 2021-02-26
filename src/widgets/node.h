#ifndef NODE_H
#define NODE_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include "widgets/edge.h"
#include "common/error.h"

class NodeError : public Error {
public:
    enum id {
        GENERIC,
        INVALID_ARGUMENT,

        INVALID_NODE_NAME,
        PASSED_EDGE_DOES_NOT_CONTAIN_NODE
    };

    NodeError( id error_id = GENERIC, QString message = "" ) :
        Error( (Error::id)error_id, message ) { }
};

class Edge;

class Node : public QGraphicsItem
{
public:
    Node( QString name, qreal x = 0, qreal y = 0, QGraphicsItem* parent = nullptr );

    bool operator==( Node& other );
    bool operator!=( Node& other );

    QRectF boundingRect() const;
    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void addEdge( Edge* edge );

    QString getName() const;
    void setName( QString name );

private:
    QString name;
    QVector<Edge*> edges;
};

#endif // NODE_H
