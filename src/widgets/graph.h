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

#include "widgets/node.h"
#include "common/error.h"

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

public:
    enum Action {
        REMOVE_NODE,
        CREATE_NODE,
        CREATE_EDGE
    };

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

    bool load( QString filepath );
    bool save( QString filepath );

    void requestUserAction( Action action );

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
        qDebug() << event->scenePos();
        QGraphicsScene::mouseMoveEvent( event );
    }


    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QVector<Node*> nodes;
    QVector<Edge*> edges;

    bool nodeRemovalRequested;
    bool nodeCreationRequested;
    bool edgeCreationRequested;
    Node* edgeCreationHold;

};

#endif // GRAPH_H
