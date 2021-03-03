#include "graphview.h"

GraphView::GraphView(Graph* graph, QWidget* parent ) :
    QGraphicsView( parent ), graph( graph )
{
    this->setScene( graph );
    this->setRenderHint(QPainter::Antialiasing, true );
    this->setMouseTracking( true );

    graph->setSceneRect(-10000,-10000,20000,20000);

    //setDragMode(ScrollHandDrag);
    //setDragMode(DragMode::)
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

void GraphView::wheelEvent(QWheelEvent *event) {
    if( event->angleDelta().y() > 0 ) {
        qDebug() << "zoomin";
        this->scale( 1.1, 1.1 );
    } else {
        qDebug() << "zoomout";
        this->scale( 0.9, 0.9 );
    }

    if( event->modifiers().testFlag(Qt::ControlModifier) ) {
        qDebug() << "ctrl";
    }
}

void GraphView::keyPressEvent(QKeyEvent *event) {
    if( event->key() == Qt::Key_Space && !event->isAutoRepeat() ) {
        qDebug() << "Space pressed";
        setDragMode(DragMode::ScrollHandDrag);
    }
}

void GraphView::keyReleaseEvent(QKeyEvent *event) {
    if( event->key() == Qt::Key_Space && !event->isAutoRepeat() ) {
        qDebug() << "Space unpressed";
        setDragMode(DragMode::NoDrag);
    }
}
