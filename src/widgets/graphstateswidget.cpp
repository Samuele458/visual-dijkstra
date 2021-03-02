#include "graphstateswidget.h"

GraphStatesWidget::GraphStatesWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout( this );
    statesTitle = new QLabel;
    table = new GraphStatesTable;

    layout->addWidget( statesTitle );
    layout->addWidget( table );

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
