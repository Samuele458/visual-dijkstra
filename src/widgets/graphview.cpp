#include "graphview.h"

GraphView::GraphView(Graph* graph, QWidget* parent ) :
    QGraphicsView( parent ), graph( graph )
{
    this->setScene( graph );
    this->setRenderHint(QPainter::Antialiasing, true );
    this->setMouseTracking( true );
    this->viewport()->setCursor(Qt::CrossCursor);

}


GraphView::GraphView( QWidget* parent ) :
    GraphView( new Graph(), parent )
{

}

Graph* GraphView::getGraph() const {
    return this->graph;
}

void GraphView::setGraph( Graph* graph ) {
    this->graph = graph;
}
