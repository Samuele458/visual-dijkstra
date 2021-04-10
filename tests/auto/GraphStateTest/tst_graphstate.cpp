#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QDebug>
#include <QtWidgets>
#include <QPushButton>


#include "common/graphstate.h"
#include "widgets/graphview.h"


class GraphStateTest : public QObject {
    Q_OBJECT

private slots:
    void stateCreatedByNodesVector_NodesEntered();
};

void GraphStateTest::stateCreatedByNodesVector_NodesEntered() {
    QVector<NodeState> nodes;
    nodes.push_back( NodeState("A") );
    nodes.push_back( NodeState("B") );
    nodes.push_back( NodeState("C") );
    nodes.push_back( NodeState("D") );
    GraphState graph( nodes );

    QVERIFY( graph.getNodes().size() == 4 );

    NodeState hold = graph.getNodes().at(0);
    QVERIFY( hold == NodeState("A") );

    hold = graph.getNodes().at(1);
    QVERIFY( hold == NodeState("B") );

    hold = graph.getNodes().at(2);
    QVERIFY( hold == NodeState("C") );

    hold = graph.getNodes().at(3);
    QVERIFY( hold == NodeState("D") );

    // testing GraphState::setNodes();
    nodes.clear();
    nodes.push_back( NodeState("E" ) );

    graph.setNodes( nodes );

    QVERIFY( graph.getNodes().size() == 1 );

    hold = graph.getNodes().at(0);
    QVERIFY( hold == NodeState("E") );

    Graph g;
}


QTEST_MAIN(GraphStateTest)


#include "tst_nodestate.moc"
