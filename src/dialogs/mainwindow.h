#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include "widgets/node.h"
#include "widgets/edge.h"
#include "widgets/graph.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow() {};
private:

    QToolBar* toolbar;

    QGraphicsView* editorView;
    //QGraphicsScene* scene;
    Graph* graph;
    Node* node1;
    Node* node2;
    Edge* edge1;

};

#endif
