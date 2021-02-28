#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include <QDebug>
#include <QWheelEvent>

#include "widgets/graph.h"

class GraphView : public QGraphicsView
{
public:
    GraphView( Graph* graph, QWidget* parent = nullptr );
    GraphView( QWidget* parent = nullptr  );

    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    Graph* getGraph() const;
    void setGraph( Graph* graph );
private:
    Graph* graph;
};

#endif // GRAPHVIEW_H
