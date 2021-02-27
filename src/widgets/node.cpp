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

#include "node.h"

Node::Node(QString name, qreal x, qreal y, QGraphicsItem* parent ) : QGraphicsItem(parent)
{
    this->name = name;

    this->setFlag(QGraphicsItem::ItemIsMovable,true);

    backgroundColor = Qt::white;
    borderColor = Qt::black;

    //item position
    this->setPos( x, y );
}

//Equal operator. Comparison based on node name.
bool Node::operator==( Node& other ) {
    return ( this->name == other.name );
}

//opposite of Equal operator
bool Node::operator!=( Node& other ) {
    return !( operator==( other ) );
}

QRectF Node::boundingRect() const
{
    return QRectF(0,0,30,30);
}


void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //item area
    QRectF bound = boundingRect();

    //brush for item background
    QBrush brush(backgroundColor);

    //bruch for contours
    QBrush contourBrush(borderColor);
    QPen pen( contourBrush, 3 );

    painter->setBrush( brush );
    painter->setPen( pen );

    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont( font );


    //painter->drawRect(rect);
    painter->drawEllipse(0,0,bound.width(),bound.height());
    painter->drawText(0,0,bound.width(),bound.height(),Qt::AlignCenter,name);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //refreshing each edge
    QVectorIterator<Edge*> i(edges);
    while(i.hasNext())
        i.next()->update();

    QGraphicsItem::mouseMoveEvent( event );
}

void Node::addEdge(Edge* edge)
{
    //the edge must contain THIS node.
    if( edge->getNodeA() != this && edge->getNodeB() != this ) {
        throw NodeError( NodeError::PASSED_EDGE_DOES_NOT_CONTAIN_NODE, "Edge does not contain this node" );
    }

    edges.push_back(edge);
}

void Node::removeEdge( Edge* edge ) {
    for( int i = 0; i < edges.size(); ++i ) {
        if( edges.at(i) == edge ) {
            edges.removeAt( i );
        }
    }
}

QVector<Edge*> Node::getEdges() const {
    return edges;
}

QString Node::getName() const {
    return this->name;
}

void Node::setName( QString name ) {
    this->name = name;
}

QPointF Node::getCenter() const {
    return QPointF( x()+boundingRect().width()/2, y()+boundingRect().height()/2 );
}

void Node::setBackgroundColor( QColor color ) {
    backgroundColor = color;
}

void Node::setBorderColor( QColor color ) {
    borderColor = color;
}

QColor Node::getBackgroundColor() const {
    return backgroundColor;
}

QColor Node::getBorderColor() const {
    return borderColor;
}


