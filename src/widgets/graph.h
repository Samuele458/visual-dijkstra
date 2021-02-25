#ifndef GRAPH_H
#define GRAPH_H
#include <QGraphicsScene>
#include <QVector>
#include <QString>

#include "widgets/node.h"

class Graph : public QGraphicsScene
{

public:
    Graph(QObject* parent = nullptr);

    void addNode( Node* node );
    void addNode( QString name, qreal x, qreal y );

private:
    QVector<Node*> nodes;

};

#endif // GRAPH_H
