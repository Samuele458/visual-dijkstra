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
#include <QAction>
#include <QFileDialog>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QCloseEvent>
#include <QApplication>

#include "widgets/node.h"
#include "widgets/edge.h"
#include "widgets/graph.h"
#include "widgets/graphview.h"
#include "widgets/graphpathfinderview.h"
#include "dialogs/licensedialog.h"
#include "dialogs/aboutdialog.h"
#include "widgets/graphstatestable.h"
#include "widgets/graphstateswidget.h"
#include "common/settingsmanager.h"
#include "dialogs/settingsdialog.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow() {};

    //event close
    void closeEvent( QCloseEvent* event ) override;

    //context menu
    void contextMenuEvent(QContextMenuEvent *event) override;

protected slots:
    void open_action_slot();
    void exit_action_slot();
    void save_action_slot();
    void save_as_action_slot();
    void remove_node_action_slot();
    void create_node_action_slot();
    void create_edge_action_slot();
    void license_action_slot();
    void about_action_slot();
    void calculate_path_action_slot();
    void new_graph_action_slot();
    void settings_action_slot();

private:

    //allocating and configuring actions
    void createActions();

    //allocating and configuring menus
    void createMenus();

    // ---- actions ----
    QAction* exitAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* removeNodeAction;
    QAction* createNodeAction;
    QAction* createEdgeAction;
    QAction* licenseAction;
    QAction* aboutAction;
    QAction* calculatePathAction;
    QAction* newGraphAction;
    QAction* settingsAction;


    // ---- widgets ----
    QToolBar* toolbar;
    GraphPathfinderView* graphView;

    GraphStatesWidget* table;
    QSplitter* tableSplitter;


    // -- menus --
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* helpMenu;


    bool saved;
    QString saveFile;


};

#endif
