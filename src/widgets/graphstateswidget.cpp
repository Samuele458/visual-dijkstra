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

#include "graphstateswidget.h"

GraphStatesWidget::GraphStatesWidget(QWidget *parent) : QWidget(parent)
{
    graphView = nullptr;

    layout = new QVBoxLayout( this );
    statesTitle = new QLabel;
    table = new GraphStatesTable;
    grid = new QWidget;
    statesGrid = new QGridLayout;
    splitter = new QSplitter;
    buttonsArea = new QScrollArea;


    layout->setMargin(0);

    statesGrid->setSizeConstraint( QLayout::SetMaximumSize );

    //grid->setLayout( statesGrid );
    statesGrid->setMargin(0);

    statesGrid->setSpacing(2);



    grid->setLayout( statesGrid );
    buttonsArea->setWidgetResizable(true);
    buttonsArea->setWidget( grid );
    buttonsArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    splitter->setOrientation( Qt::Vertical );
    splitter->addWidget( buttonsArea );
    splitter->addWidget( table );
    splitter->setSizes( QList<int>() << 200 << 400 );

    statesTitle->setText("Steps");
    layout->addWidget( statesTitle );
    layout->addWidget(splitter);

    this->setLayout( layout );


}

QVector<GraphState> GraphStatesWidget::getStates() const {
    return this->states;
}

void GraphStatesWidget::setStates( QVector<GraphState> states ) {
    this->states = states;

    //deleting old buttons
    for( int i = 0; i < statesButtons.size(); ++i ) {
        statesGrid->removeWidget( statesButtons.at(i) );
        delete statesButtons.at(i);
    }

    statesButtons.clear();

    //creating new buttons
    for( int i = 0; i < states.size(); ++i ) {

        //new button
        QPushButton* button = new QPushButton(QString::number(i));

        if( states.at(i).getMessage() != "" ) {
            button->setToolTip(states.at(i).getMessage());
        }


        statesButtons.push_back( button );
        statesButtons.at(i)->setMinimumWidth(20);
        statesButtons.at(i)->setMinimumHeight(30);

        connect( button, SIGNAL(clicked()), this, SLOT(state_button_clicked()));
    }

    applyState( states.size() - 1 );
    refresh();
}

void GraphStatesWidget::addState( GraphState state ) {
    states.push_back( state );

    //deleting old buttons
    for( int i = 0; i < statesButtons.size(); ++i ) {
        statesGrid->removeWidget( statesButtons.at(i) );
        delete statesButtons.at(i);
    }

    statesButtons.clear();

    //creating new buttons
    for( int i = 0; i < states.size(); ++i ) {
        statesButtons.push_back( new QPushButton(QString::number(i)));
        statesButtons.at(i)->setMinimumWidth(20);
    }

    refresh();
}

void GraphStatesWidget::clearStates() {
    states.clear();

    //deleting old buttons
    for( int i = 0; i < statesButtons.size(); ++i ) {
        statesGrid->removeWidget( statesButtons.at(i) );
        delete statesButtons.at(i);
    }

    table->clearContents();
    table->setRowCount(0);

    statesButtons.clear();

    //reset default graph
    if( graphView != nullptr ) {
        graphView->getGraph()->resetState();
    }

    refresh();
}

void GraphStatesWidget::refresh() {
    int colCount = this->size().width()/50;

    for( int i = 0; i < statesButtons.size(); ++i ) {
        statesGrid->removeWidget( statesButtons.at(i) );
    }

    int current = 0;
    for( int i = 0; current < statesButtons.size()  ; ++i ) {
        for( int j = 0; j < colCount; ++j ) {

            if( !(current < statesButtons.size() )) {
                break;
            }
            statesGrid->addWidget( statesButtons.at(current),i,j);
            ++current;
        }

    }
}

void GraphStatesWidget::resizeEvent(QResizeEvent *event) {
    Q_UNUSED( event );

    refresh();
}

//apply state
void GraphStatesWidget::applyState( int pos ) {
    if( pos >= 0 && pos < states.size() ) {
        table->setState( states.at( pos ) );

        QVectorIterator<QPushButton*> i(statesButtons);
        while( i.hasNext() ) {
            QPushButton* button = i.next();
            if( button == statesButtons.at(pos) ) {
                button->setStyleSheet("background-color: rgba(46, 204, 113, 0.4); border:none;");
            } else {
                button->setStyleSheet("background-color: rgba(150, 204, 113, 0.4); border:none;");
            }
        }

        //check if graphView is set
        if( graphView != nullptr ) {

            //setting state to graphView
            graphView->getGraph()->highlightState( states.at(pos), true );


        }
    }
    else {
        table->clearContents();
    }
}


void GraphStatesWidget::setGraphPathfinderView( GraphPathfinderView* view ) {
    this->graphView = view;
}

GraphPathfinderView* GraphStatesWidget::getGraphPathfinderView() const {
    return graphView;
}

// ----

void GraphStatesWidget::state_button_clicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int index = button->text().toInt();

    applyState( index );

}
