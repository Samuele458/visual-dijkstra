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
#include "widgets/graphview.h"
#include "common/adjacencymatrix.h"


class AdjacencyMatrixTest : public QObject {
    Q_OBJECT

private slots:
    void constructMatrix_MatrixCreated();
    void nullGraph_VoidMatrix();
    void validGraph_MatrixCreated();

};

void AdjacencyMatrixTest::constructMatrix_MatrixCreated() {
    Graph graphObj;
    graphObj.addNode("A", 0, 0);
    graphObj.addNode("B", 50, 50);
    graphObj.addNode("C", 100, 100);

    AdjacencyMatrix matrix(&graphObj);

}

void AdjacencyMatrixTest::nullGraph_VoidMatrix() {
    AdjacencyMatrix matrix(nullptr);

    QVERIFY( matrix.getNodes().size() == 0 );
    QVERIFY( matrix.getMatrix().size() == 0 );
}

void AdjacencyMatrixTest::validGraph_MatrixCreated() {
    Graph graph1;
    graph1.addNode("A", 0, 0);
    graph1.addNode("B", 50, 50);
    graph1.addNode("C", 100, 100);

    AdjacencyMatrix matrix(&graph1);
    QVERIFY( matrix.getNodes() == QStringList() << "A" << "B" << "C" );
    QVERIFY( matrix.getMatrix() == QVector<QVector<int>>({
                                                             {0,0,0},
                                                             {0,0,0},
                                                             {0,0,0}
                                                         }));

    //---

    graph1.addEdge("A", "B", 5);
    matrix.generate();
    QVERIFY( matrix.getNodes() == QStringList() << "A" << "B" << "C" );
    QVERIFY( matrix.getMatrix() == QVector<QVector<int>>({
                                                             {0,1,0},
                                                             {1,0,0},
                                                             {0,0,0}
                                                         }));

    //---

    graph1.addEdge("B", "C", 5);
    graph1.addEdge("A", "C", 5);
    matrix.generate();
    matrix.setGraph(&graph1);
    QVERIFY( matrix.getNodes() == QStringList() << "A" << "B" << "C" );
    QVERIFY( matrix.getMatrix() == QVector<QVector<int>>({
                                                             {0,1,1},
                                                             {1,0,1},
                                                             {1,1,0}
                                                         }));

}



QTEST_MAIN(AdjacencyMatrixTest)
#include "tst_adjacencymatrix.moc"
