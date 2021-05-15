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

#ifndef GRAPH_H
#define GRAPH_H
#include <QGraphicsScene>
#include <QVector>
#include <QString>
#include <QSettings>
#include <QFile>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <QDir>
#include <QEvent>
#include <QColor>
#include <QMessageBox>
#include <QAction>
#include <QMenu>

#include "widgets/node.h"
#include "common/error.h"
#include "common/graphstate.h"


class GraphState;

class GraphError : public Error {
public:
    enum id {
        GENERIC,
        INVALID_ARGUMENT,

        DUPLICATED_NODE,
        DUPLICATED_EDGE,
        UNKNOWN_NODE
    };

    GraphError( id error_id = GENERIC, QString message = "" ) :
        Error( (Error::id)error_id, message ) { }

};


class Graph : public QGraphicsScene
{
    Q_OBJECT


public:

    //action requested
    enum Action {
        REMOVE_NODE,
        CREATE_NODE,
        CREATE_EDGE
    };

    //default color for lines, and nodes borders
    static QColor DEFAULT_LINE_COLOR;

    //default background color for nodes
    static QColor DEFAULT_ITEM_COLOR;

    //highlighted color for lines, and nodes borders
    static QColor HIGHLIGHT_LINE_COLOR;

    //highlighted background color for nodes
    static QColor HIGHLIGHT_ITEM_COLOR;

    //Path color for nodes
    static QColor PATH_ITEM_COLOR;

    //line color for nodes and edges
    static QColor PATH_LINE_COLOR;

    Graph(QObject* parent = nullptr);

    void addNode( Node* node );
    void addNode( QString name, qreal x, qreal y );

    void addEdge( QString nameA, QString nameB, int weight = 3 );
    void addEdge( Node* nodeA, Node* nodeB, int weight = 3 );
    void addEdge( Edge* edge );

    void removeEdge( QString nameA, QString nameB );
    void removeEdge( Node* nodeA, Node* nodeB );
    void removeEdge( Edge* edge );

    void removeNode( QString name );
    void removeNode( Node* node );

    Node* getNode( QString name ) const;
    QVector<Node*> getNodes() const;

    void highlightState( GraphState state, bool drawPath = false );
    void resetState();

    bool load( QString filepath );
    bool save( QString filepath );

    void emptyGraph();

    void requestUserAction( Action action );

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
        //qDebug() << event->scenePos();
        QGraphicsScene::mouseMoveEvent( event );
    }

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


    void resetRequest();

    QString toString();

    bool isSaved();

protected slots:
    void remove_node_action_slot();
    void remove_edge_action_slot();
    void edit_node_action_slot();
    void edit_edge_action_slot();

private:
    void createActions();

    QAction* removeNodeAction;
    QAction* editNodeAction;
    QAction* removeEdgeAction;
    QAction* editEdgeAction;
    QAction* newNodeAction;

    QVector<Node*> nodes;
    QVector<Edge*> edges;

    // user actions flags
    bool nodeRemovalRequested;
    bool nodeCreationRequested;
    bool edgeCreationRequested;
    Node* edgeCreationHold;

    QGraphicsItem* contextMenuItemHold;

    //indicates if file is saved
    bool saved;

};


#endif // GRAPH_H
