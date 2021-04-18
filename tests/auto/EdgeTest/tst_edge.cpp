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

#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QDebug>
#include <QtWidgets>
#include <QColor>

#include "widgets/node.h"
#include "widgets/edge.h"


class EdgeTest : public QObject {
    Q_OBJECT

private slots:
    void constructEdge_EdgeCreated();
    void constructEdgeWithEqualNodes_ExceptionThrown();
    void constructEdgeWithInvalidWeight_ExceptionThrown();
    void testStyle();
};


void EdgeTest::constructEdge_EdgeCreated() {
    Node nodeA("A");
    Node nodeB("B");

    Edge edge(&nodeA, &nodeB, 5 );

    QVERIFY( edge.getNodeA() == &nodeA );
    QVERIFY( edge.getNodeB() == &nodeB );
}

void EdgeTest::constructEdgeWithEqualNodes_ExceptionThrown() {
    Node nodeA("A");

    QVERIFY_EXCEPTION_THROWN( Edge(&nodeA, &nodeA, 5 ), EdgeError );

    Node nodeB("B");
    Node otherNode("B");

    QVERIFY_EXCEPTION_THROWN( Edge( &nodeB, &otherNode, 5 ), EdgeError );
}

void EdgeTest::constructEdgeWithInvalidWeight_ExceptionThrown() {
    Node nodeA("A");
    Node nodeB("B");

    QVERIFY_EXCEPTION_THROWN( Edge( &nodeA, &nodeB, -5 ), EdgeError );

}

void EdgeTest::testStyle() {
    Node nodeA("A");
    Node nodeB("B");

    Edge edge(&nodeA, &nodeB, 5 );

    edge.setColor( Qt::red );
    QVERIFY( edge.getColor() == Qt::red );
}


QTEST_MAIN(EdgeTest)
#include "tst_edge.moc"
