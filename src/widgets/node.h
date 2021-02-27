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

#ifndef NODE_H
#define NODE_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include "widgets/edge.h"
#include "common/error.h"

class NodeError : public Error {
public:
    enum id {
        GENERIC,
        INVALID_ARGUMENT,

        INVALID_NODE_NAME,
        PASSED_EDGE_DOES_NOT_CONTAIN_NODE
    };

    NodeError( id error_id = GENERIC, QString message = "" ) :
        Error( (Error::id)error_id, message ) { }
};

class Edge;

class Node : public QGraphicsItem
{
public:
    //allow the use of qgraphicsitem_cast
    enum { Type = UserType + 1 };
    int type() const override { return Type; }


    Node( QString name, qreal x = 0, qreal y = 0, QGraphicsItem* parent = nullptr );

    bool operator==( Node& other );
    bool operator!=( Node& other );

    QRectF boundingRect() const;
    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void addEdge( Edge* edge );
    void removeEdge( Edge* edge );
    QVector<Edge*> getEdges() const;

    QString getName() const;
    void setName( QString name );

    QPointF getCenter() const;
private:
    QString name;
    QVector<Edge*> edges;
};

#endif // NODE_H
