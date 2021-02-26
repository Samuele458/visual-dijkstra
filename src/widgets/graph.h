#ifndef GRAPH_H
#define GRAPH_H
#include <QGraphicsScene>
#include <QVector>
#include <QString>
#include <QSettings>

#include "widgets/node.h"

class Graph : public QGraphicsScene
{

public:
    Graph(QObject* parent = nullptr);

    bool addNode( Node* node );
    bool addNode( QString name, qreal x, qreal y );

    bool addEdge( QString nameA, QString nameB, int weight = 3 );
    bool addEdge( Node* nodeA, Node* nodeB, int weight = 3 );

    bool load( QString filepath );
    bool save( QString filepath );

private:
    QVector<Node*> nodes;
    QVector<Node*> edges;

};

#endif // GRAPH_H
