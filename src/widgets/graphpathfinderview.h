/*          Visual Dijkstra
 *    Copyright (C) 2021 Samuele Girgenti
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * 	     --  CONTACTS --
 *   Email:      samuele.girgenti458@gmail.com
 *   Github:     https://github.com/Samuele458
 */

#ifndef GRAPHPATHFINDERVIEW_H
#define GRAPHPATHFINDERVIEW_H

#include "graphview.h"
#include "widgets/graphstateswidget.h"
#include "common/graphstate.h"

class GraphStatesWidget;

class GraphPathfinderView : public GraphView
{
public:

    //action requested
    enum Action {
        CALCULATE_PATH
    };

    GraphPathfinderView( Graph* graph, QWidget* parent = nullptr );
    GraphPathfinderView( QWidget* parent = nullptr  );

    void requestUserAction( Action action );

    void resetRequest();

    void mousePressEvent(QMouseEvent *event) override;

    QVector<GraphState> dijkstraAlgorithm( Node* source, Node* dest );

    void setStatesWidget( GraphStatesWidget* widget );
    GraphStatesWidget* getStatesWidget() const;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:

    GraphStatesWidget* statesWidget;

    // user actions flags
    bool pathCalculationRequested;
    Node* pathCalculationHold;
};

#endif // GRAPHPATHFINDERVIEW_H
