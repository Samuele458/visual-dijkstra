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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QTableWidget>
#include <QSplitter>

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

    QWidget* mainWidget;
    QHBoxLayout* mainLayout;
    QTableWidget* table;
    QSplitter* tableSplitter;


    Graph* graph;
    Node* node1;
    Node* node2;
    Edge* edge1;


};

#endif
