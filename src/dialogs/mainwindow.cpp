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

#include "dialogs/mainwindow.h"


MainWindow::MainWindow( QWidget* parent ) : QMainWindow(parent) {


    /*
    SettingsManager man("config.ini");
    man.setValue("style",
                 "widgets-background-color",
                 "red");

    qDebug() << man.getValue("style",
                 "widget-text-color"
                 );
    */

    //TODO: apply styles
    //((QApplication*)QApplication::instance())->setStyleSheet("QMainWindow { background-color: red }");

    //creating actions
    createActions();

    //creating menus
    createMenus();

    //window toolbar
    toolbar = new QToolBar("Visual Dijkstra");
    this->addToolBar( toolbar );
    toolbar->addAction( newGraphAction );
    toolbar->addAction( openAction );
    toolbar->addAction( saveAction );
    toolbar->addSeparator();
    toolbar->addAction( createNodeAction );
    toolbar->addAction( removeNodeAction );
    toolbar->addAction( createEdgeAction );
    toolbar->addSeparator();
    toolbar->addAction( calculatePathAction );

    //setup UI
    graphView = new GraphPathfinderView;
    table = new GraphStatesWidget;
    tableSplitter =  new QSplitter(Qt::Orientation::Horizontal);

    tableSplitter->addWidget(graphView);
    tableSplitter->addWidget( table );
    tableSplitter->setSizes( QList<int>() << 600 << 200 );
    tableSplitter->setCollapsible( 1, false );

    this->setCentralWidget( tableSplitter );
    this->setContentsMargins(5,0,5,5);

    //maximize window
    this->showMaximized();
    //this->setMinimumSize( 900, 600 );

    graphView->setStatesWidget( table );
    table->setGraphPathfinderView( graphView );

    // ----
    saved = false;
    saveFile = "";

    settings = new SettingsManager("config.ini");
    applySettings();
}

void MainWindow::createActions() {
    exitAction = new QAction( "Exit", this );
    exitAction->setShortcut( QKeySequence::Quit );
    exitAction->setIcon( QIcon(":/data/icons/logout.png") );
    connect( exitAction, SIGNAL(triggered()), this, SLOT(exit_action_slot()) );

    openAction = new QAction( "Open", this );
    openAction->setIcon( QIcon(":/data/icons/folder.png") );
    connect( openAction, SIGNAL(triggered()), this, SLOT(open_action_slot()) );

    saveAction = new QAction( "Save", this );
    saveAction->setIcon( QIcon(":/data/icons/save.png") );
    connect( saveAction, SIGNAL(triggered()), this, SLOT(save_action_slot()) );

    saveAsAction = new QAction( "Save as...", this );
    saveAsAction->setIcon( QIcon(":/data/icons/save.png") );
    connect( saveAsAction, SIGNAL(triggered()), this, SLOT(save_as_action_slot()) );

    removeNodeAction = new QAction( "Remove node", this );
    removeNodeAction->setIcon( QIcon(":/data/icons/delete.png") );
    removeNodeAction->setToolTip( "Remove node. Click on a node to remove it.");
    connect( removeNodeAction, SIGNAL(triggered()), this, SLOT(remove_node_action_slot()) );

    createNodeAction = new QAction( "Create node", this );
    createNodeAction->setIcon( QIcon(":/data/icons/add.png") );
    connect( createNodeAction, SIGNAL(triggered()), this, SLOT(create_node_action_slot()) );

    createEdgeAction = new QAction( "Create edge", this );
    createEdgeAction->setIcon( QIcon(":/data/icons/route.png") );
    createEdgeAction->setToolTip( "Create new edge. Click on two nodes to link them.");
    connect( createEdgeAction, SIGNAL(triggered()), this, SLOT(create_edge_action_slot()) );

    licenseAction = new QAction( "Show License", this );
    licenseAction->setIcon( QIcon(":/data/icons/license.png") );
    connect( licenseAction, SIGNAL(triggered()), this, SLOT(license_action_slot()) );

    aboutAction = new QAction( "About", this );
    aboutAction->setIcon( QIcon(":/data/icons/info.png") );
    connect( aboutAction, SIGNAL(triggered()), this, SLOT(about_action_slot()) );

    calculatePathAction = new QAction( "Calculate Path", this );
    calculatePathAction->setIcon( QIcon(":/data/icons/path.png") );
    calculatePathAction->setToolTip( "Calculate path between two nodes. Click on two nodes to calculate the path.");
    connect( calculatePathAction, SIGNAL(triggered()), this, SLOT(calculate_path_action_slot()) );

    newGraphAction = new QAction( "Create new graph", this );
    newGraphAction->setIcon( QIcon(":/data/icons/new.png") );
    connect( newGraphAction, SIGNAL(triggered()), this, SLOT(new_graph_action_slot()) );


    settingsAction = new QAction( "Open settings dialog", this );
    connect( settingsAction, SIGNAL(triggered()), this, SLOT(settings_action_slot()));
}

//allocating and configuring menus
void MainWindow::createMenus() {

    //File menu
    fileMenu = menuBar()->addMenu( "File" );
    fileMenu->addAction(newGraphAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    //Edit menu
    editMenu = menuBar()->addMenu( "Edit" );
    editMenu->addAction( createNodeAction );
    editMenu->addAction( removeNodeAction );
    editMenu->addSeparator();
    editMenu->addAction( createEdgeAction );
    editMenu->addSeparator();
    editMenu->addAction( calculatePathAction );
    editMenu->addAction( settingsAction );

    //Help menu
    helpMenu = menuBar()->addMenu( "Help" );
    helpMenu->addAction( aboutAction );
    helpMenu->addAction( licenseAction );
}


// ---- Actions ----

void MainWindow::open_action_slot() {
    graphView->resetRequest();
    QString filename = "";
    //checking that file is saved before opening a new one
    if( graphView->getGraph()->isSaved() ) {
#ifdef _WIN32
            filename = QFileDialog::getOpenFileName( this, "Open file", "", "Config (*.ini);;Others (*.*)", nullptr );
#else
            filename = QFileDialog::getOpenFileName( this, "Open file", "", "Others (*)", nullptr );
#endif
        if( filename != "" ) {
            if( graphView->getGraph()->load( filename ) ) {
                saved = true;
                saveFile = filename;
            } else {
                saved = false;
                saveFile = "";
            }
        }
    } else {
        //file unsaved
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Save graph","Want to save current Graph?",
                    QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        if( reply == QMessageBox::Yes ) {
            //YES button clicked
            save_action_slot();
        }

        if( reply != QMessageBox::Cancel ) {
#ifdef _WIN32
            filename = QFileDialog::getOpenFileName( this, "Open file", "", "Config (*.ini);;Others (*.*)", nullptr );
#else
            filename = QFileDialog::getOpenFileName( this, "Open file", "", "Others (*)", nullptr );
#endif
            if( filename != "" ) {
                if( graphView->getGraph()->load( filename ) ) {
                    saved = true;
                    saveFile = filename;
                } else {
                    saved = false;
                    saveFile = "";
                }
            }
        }
    }
}

void MainWindow::exit_action_slot() {
    this->close();
}

void MainWindow::save_action_slot() {
    graphView->resetRequest();
    if( saveFile != ""  ) {
        if( !graphView->getGraph()->save( saveFile ) ) {
            QMessageBox::critical( nullptr, "Error", "Could not open file" );
        }
    } else {
        save_as_action_slot();
    }
}

void MainWindow::save_as_action_slot() {
    graphView->resetRequest();
    QString filename = QFileDialog::getSaveFileName( this, "Save as...", "", "Config (*.ini);;Others (*.*)" );

    if( filename != "" ) {
        if( graphView->getGraph()->save( filename ) ) {
            saved = true;
            saveFile = filename;
        } else {
            QMessageBox::critical( nullptr, "Error", "Could not open file" );
        }
    }
}

void MainWindow::remove_node_action_slot() {
    graphView->resetRequest();
    graphView->getGraph()->requestUserAction( Graph::REMOVE_NODE );
}

void MainWindow::create_node_action_slot() {
    graphView->resetRequest();
    graphView->getGraph()->requestUserAction( Graph::CREATE_NODE );
}

void MainWindow::create_edge_action_slot() {
    graphView->resetRequest();
    graphView->getGraph()->requestUserAction( Graph::CREATE_EDGE );

}

void MainWindow::license_action_slot() {
    //reset any pending request
    graphView->resetRequest();
    graphView->getGraph()->resetRequest();


    LicenseDialog* license_dialog = new LicenseDialog( this );

    license_dialog->exec();

    delete license_dialog;
}

void MainWindow::about_action_slot() {
    //reset any pending request
    graphView->resetRequest();
    graphView->getGraph()->resetRequest();


    AboutDialog* about_dialog = new AboutDialog( this );

    about_dialog->exec();

    delete about_dialog;
}

void MainWindow::calculate_path_action_slot() {
    //reset any pending request
    graphView->getGraph()->resetRequest();

    graphView->requestUserAction( GraphPathfinderView::CALCULATE_PATH );
}

void MainWindow::new_graph_action_slot() {
    graphView->resetRequest();
    graphView->getGraph()->resetRequest();

    //check if graph is saved before creating a new one
    if( !graphView->getGraph()->isSaved() ) {
        //file unsaved
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Save graph","Want to save current Graph?",
                    QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if( reply != QMessageBox::Cancel ) {
            if( reply == QMessageBox::Yes ) {
                save_action_slot();
            }
            graphView->getGraph()->emptyGraph();

        }
    }
}

void MainWindow::settings_action_slot() {

    SettingsDialog* dialog = new SettingsDialog(settings);

    dialog->exec();

    delete dialog;

    applySettings();
}

//event close
void MainWindow::closeEvent( QCloseEvent* event ) {
    Q_UNUSED( event );

    if( !graphView->getGraph()->isSaved() ) {

        //file unsaved
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Save graph","Want to save current Graph?",
                    QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        if( reply == QMessageBox::Yes ) {
            //YES button clicked
            save_action_slot();

            event->accept();
        } else if( reply == QMessageBox::No ) {
            //NO button clicked

            event->accept();

        } else if( reply == QMessageBox::Cancel ) {
            //Cancel button clicked

            event->ignore();
        }

    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
    //reset any pending request
    graphView->resetRequest();
    graphView->getGraph()->resetRequest();

    QMainWindow::contextMenuEvent( event );

}

void MainWindow::applySettings()
{
    qDebug() << "QWidget { background-color: "+settings->getValue("style","widgets-background-color").toString()+" }";
    ((QApplication*)QApplication::instance())
            ->setStyleSheet("QWidget { background-color: "+settings->getValue("style","widgets-background-color").toString()+" }");
}
