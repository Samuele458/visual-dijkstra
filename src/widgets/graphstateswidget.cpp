#include "graphstateswidget.h"

GraphStatesWidget::GraphStatesWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout( this );
    statesTitle = new QLabel;
    table = new GraphStatesTable;
    grid = new QWidget;
    statesGrid = new QGridLayout;
    splitter = new QSplitter;
    buttonsArea = new QScrollArea;

    //statesGrid->setSizeConstraint( QLayout::SetMaximumSize );

    layout->setMargin(0);


    //grid->setLayout( statesGrid );
    statesGrid->setMargin(0);

    statesGrid->setSpacing(2);

    for( int i = 0; i < 300; ++i ) {
        statesButtons.push_back( new QPushButton(QString::number(i)));
        statesButtons.at(i)->setMinimumWidth(20);
    }

    grid->setLayout( statesGrid );
    buttonsArea->setWidgetResizable(true);
    buttonsArea->setWidget( grid );
    buttonsArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


    splitter->setOrientation( Qt::Vertical );
    splitter->addWidget( buttonsArea );
    splitter->addWidget( table );
    splitter->setSizes( QList<int>() << 200 << 400 );

    statesTitle->setText("States");
    layout->addWidget( statesTitle );
    layout->addWidget(splitter);

    this->setLayout( layout );



}

QVector<GraphState> GraphStatesWidget::getStates() const {
    return this->states;
}

void GraphStatesWidget::setStates( QVector<GraphState> states ) {
    this->states = states;
    refresh();
}

void GraphStatesWidget::addState( GraphState state ) {
    states.push_back( state );
    refresh();
}

void GraphStatesWidget::clearStates() {
    states.clear();
    refresh();
}

void GraphStatesWidget::refresh() {

}
