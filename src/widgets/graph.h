#ifndef GRAPH_H
#define GRAPH_H
#include <QGraphicsScene>
#include <QVector>
#include <QString>
#include <QSettings>

#include "widgets/node.h"
#include "common/error.h"

class GraphError : public Error {
public:
    enum id {
        GENERIC,
        INVALID_ARGUMENT,

        DUPLICATED_NODE,
        DUPLICATED_EDGE
    };

    GraphError( id error_id = GENERIC, QString message = "" ) :
        Error( (Error::id)error_id, message ) { }


};


class Graph : public QGraphicsScene
{

public:
    Graph(QObject* parent = nullptr);

    void addNode( Node* node );
    void addNode( QString name, qreal x, qreal y );

    bool addEdge( QString nameA, QString nameB, int weight = 3 );
    bool addEdge( Node* nodeA, Node* nodeB, int weight = 3 );

    bool load( QString filepath );
    bool save( QString filepath );

private:
    QVector<Node*> nodes;
    QVector<Node*> edges;

};

#endif // GRAPH_H
