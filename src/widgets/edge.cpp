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

#include "edge.h"

Edge::Edge( Node* nodeA, Node* nodeB, int weight, QGraphicsItem* parent) :
    QGraphicsItem( parent )
{
    //nodes couldn't have the same names
    if( nodeA == nodeB || nodeA->getName() == nodeB->getName() ) {
        throw EdgeError( EdgeError::INVALID_NODES, "invalid nodes");
    }

    this->nodeA = nodeA;
    this->nodeB = nodeB;
    this->weight = weight;

    //each node must have a reference to this edge
    nodeA->addEdge( this );
    nodeB->addEdge( this );

    //the lines must be behind the nodes (default Z is 0)
    this->setZValue( -1 );

    //setting default color
    color = Qt::black;
}

//Equal operator. Comparison based on node name.
bool Edge::operator==( Edge& other ) {
    return ( this->nodeA == other.nodeA ) && ( this->nodeB == other.nodeB );
}

//opposite of Equal operator
bool Edge::operator!=( Edge& other ) {
    return !( operator==( other ) );
}

Node* Edge::getNodeA() const {
    return nodeA;
}

Node* Edge::getNodeB() const {
    return nodeB;
}

int Edge::getWeight() const {
    return weight;
}

void Edge::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    bool ok;
    int weight = QInputDialog::getText(nullptr, "Set weight",
                                             "Weight:", QLineEdit::Normal,
                                             "", &ok, Qt::MSWindowsFixedSizeDialogHint ).toInt();
    this->weight = weight;
}

QPainterPath Edge::shape() const {
    //return QGraphicsItem::shape();

    QPainterPath path;
    QPolygon polygon;

    int padding = 16;
    if( ( nodeA->x() > nodeB->x() && nodeA->y() < nodeB->y() ) || ( nodeB->x() > nodeA->x() && nodeB->y() < nodeA->y() ) )
    {
        polygon << QPoint( nodeA->getCenter().x()+padding, nodeA->getCenter().y() );
        polygon << QPoint( nodeA->getCenter().x(),nodeA->getCenter().y()-padding );
        polygon << QPoint( nodeB->getCenter().x()-padding,nodeB->getCenter().y() );
        polygon << QPoint( nodeB->getCenter().x(),nodeB->getCenter().y()+padding );
        polygon << QPoint( nodeA->getCenter().x()+padding,nodeA->getCenter().y() );
    } else {
        polygon << QPoint( nodeA->getCenter().x()-padding,nodeA->getCenter().y() );
        polygon << QPoint( nodeA->getCenter().x(),nodeA->getCenter().y()-padding );
        polygon << QPoint( nodeB->getCenter().x()+padding,nodeB->getCenter().y() );
        polygon << QPoint( nodeB->getCenter().x(),nodeB->getCenter().y()+padding );
        polygon << QPoint( nodeA->getCenter().x()-padding,nodeA->getCenter().y() );
    }

    path.addPolygon( polygon );
    return path;

}

QRectF Edge::boundingRect() const {

    //nodeA coordinates
    QPointF centerA(nodeA->x(),nodeA->y());

    //nodeB coordinates
    QPointF centerB(nodeB->x(),nodeB->y());


    //points used to form the rect
    QPointF topLeft;
    QPointF bottomRight;


    //checking which is the min between centerA and centerB
    if( centerA.x() > centerB.x() ) {
        topLeft.setX( centerB.x() );
        bottomRight.setX( centerA.x() );
    } else {
        topLeft.setX( centerA.x() );
        bottomRight.setX( centerB.x() );
    }

    if( centerA.y() > centerB.y() ) {
        topLeft.setY( centerB.y() );
        bottomRight.setY( centerA.y() );
    } else {
        topLeft.setY( centerA.y() );
        bottomRight.setY( centerB.y() );
    }

    //adding padding to rect
    topLeft.setX(topLeft.x()-70);
    topLeft.setY(topLeft.y()-70);
    bottomRight.setX(bottomRight.x()+70);
    bottomRight.setY(bottomRight.y()+70);

    return QRectF(topLeft,bottomRight);
};


void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED( option );
    Q_UNUSED( widget );

    //creating pen, in order to draw line.
    painter->setPen(QPen(color, 3));

    //drawing line. The center of each nodes is calculated
    painter->drawLine(nodeA->x()+nodeA->boundingRect().width()/2,
                      nodeA->y()+nodeA->boundingRect().height()/2,
                      nodeB->x()+nodeB->boundingRect().width()/2,
                      nodeB->y()+nodeB->boundingRect().height()/2 );

    QPointF textPoint;
    QRectF bound = boundingRect();
    textPoint.setX( bound.x() + bound.width()/2 + 10 );
    textPoint.setY( bound.y() + bound.height()/2 + 10 );

    QFont font = painter->font();
    font.setPixelSize(15);
    painter->setFont( font );

    painter->drawText(textPoint,QString::number(this->weight));

};

void Edge::setColor( QColor color ) {
    this->color = color;
}

QColor Edge::getColor() const {
    return this->color;
}

