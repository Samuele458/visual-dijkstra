#ifndef GRAPHPATHFINDERVIEW_H
#define GRAPHPATHFINDERVIEW_H

#include "graphview.h"

class GraphPathfinderView : public GraphView
{
public:
    GraphPathfinderView( Graph* graph, QWidget* parent = nullptr );
    GraphPathfinderView( QWidget* parent = nullptr  );
};

#endif // GRAPHPATHFINDERVIEW_H
