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


#include "common/graphstate.h"
#include "widgets/graphview.h"


class NodeStateTest : public QObject {
    Q_OBJECT

private slots:
    void testGettersSetters();
    void testOperators();
    void invalidName_ExceptionThrown();
    void invalidDistance_ExceptionThrown();
};


void NodeStateTest::testGettersSetters() {

    NodeState nodeA("A", 3, "B", true );
    QVERIFY( nodeA.getName() == "A" );
    QVERIFY( nodeA.getDistance() == 3 );
    QVERIFY( nodeA.getPreviousNodeName() == "B" );
    QVERIFY( nodeA.isProcessed() == true );

    NodeState nodeC("C");
    QVERIFY( nodeC.getName() == "C" );
    QVERIFY( nodeC.getDistance() == NodeState::INF );
    QVERIFY( nodeC.getPreviousNodeName() == "" );
    QVERIFY( nodeC.isProcessed() == false );

    nodeA.setName("D");
    QVERIFY( nodeA.getName() == "D" );

    nodeA.setDistance(5);
    QVERIFY( nodeA.getDistance() == 5 );

    nodeA.setPreviousNodeName("E");
    QVERIFY( nodeA.getPreviousNodeName() == "E" );

    nodeA.setProcessed(true);
    QVERIFY( nodeA.isProcessed() == true );

    nodeA.setProcessed(false);
    QVERIFY( nodeA.isProcessed() == false );

}


void NodeStateTest::testOperators() {

    //test assignment operator
    NodeState nodeA("A", 3, "B", true );
    NodeState nodeB = nodeA;

    QVERIFY( nodeB.getName() == "A" );
    QVERIFY( nodeB.getDistance() == 3 );
    QVERIFY( nodeB.getPreviousNodeName() == "B" );
    QVERIFY( nodeB.isProcessed() == true );

    NodeState nodeC( "C", 5 );
    NodeState nodeD( "D", 6 );

    QVERIFY( nodeC < nodeD );
    QVERIFY( nodeC <= nodeD );
    QVERIFY( nodeD > nodeC );
    QVERIFY( nodeD >= nodeC );
    QVERIFY( nodeC != nodeD );
    QVERIFY( !(nodeC == nodeD) );
    QVERIFY( !(nodeD < nodeC) );
    QVERIFY( !(nodeD <= nodeC) );
    QVERIFY( !(nodeC > nodeD) );
    QVERIFY( !(nodeC >= nodeD) );
}


void NodeStateTest::invalidName_ExceptionThrown() {
    QVERIFY_EXCEPTION_THROWN( NodeState(""), GraphStateError );
}


void NodeStateTest::invalidDistance_ExceptionThrown() {
    QVERIFY_EXCEPTION_THROWN( NodeState("A",-4), GraphStateError );
}


QTEST_MAIN(NodeStateTest)
#include "tst_nodestate.moc"
