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

        statesButtons.push_back( button );
        statesButtons.at(i)->setMinimumWidth(20);

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

    statesButtons.clear();

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
    if( pos >= 0 && pos < states.size() )
        table->setState( states.at( pos ) );
    else table->clearContents();
}

// ----

void GraphStatesWidget::state_button_clicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int index = button->text().toInt();

    applyState( index );

}
