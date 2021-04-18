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
#include <QPushButton>

#include "widgets/node.h"
#include "widgets/edge.h"


class NodeTest : public QObject {
    Q_OBJECT

private slots:
    void constructNode_NodeCreated();
    void constructNodeWithInvalidName_ExceptionThrown();
    void addValidEdge_EdgeAdded();
    void addInvalidEdge_ExceptionThrown();

};

void NodeTest::constructNode_NodeCreated() {
    Node node("A");

    QVERIFY( node.getName() == "A" );
}

void NodeTest::constructNodeWithInvalidName_ExceptionThrown() {
    QVERIFY_EXCEPTION_THROWN( Node("+"), NodeError );
    QVERIFY_EXCEPTION_THROWN( Node("RANDOM-TEXT"), NodeError );
}

void NodeTest::addValidEdge_EdgeAdded() {
    Node nodeA("A");
    Node nodeB("B");
    Edge edge(&nodeA, &nodeB, 23 );

    nodeA.addEdge(&edge);
    nodeB.addEdge(&edge);

}

void NodeTest::addInvalidEdge_ExceptionThrown() {
    Node nodeA("A");
    Node nodeB("B");
    Node nodeC("B");
    Edge edge(&nodeA, &nodeB, 23 );

    QVERIFY_EXCEPTION_THROWN(nodeC.addEdge(&edge), NodeError);

}




QTEST_MAIN(NodeTest)
#include "tst_node.moc"
