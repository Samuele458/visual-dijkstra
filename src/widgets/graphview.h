#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include <QDebug>

#include "widgets/graph.h"

class GraphView : public QGraphicsView
{
public:
    GraphView( Graph* graph, QWidget* parent = nullptr );
    GraphView( QWidget* parent = nullptr  );


    Graph* getGraph() const;
    void setGraph( Graph* graph );
private:
    Graph* graph;
};

#endif // GRAPHVIEW_H
