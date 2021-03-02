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

#include "graphstatestable.h"

GraphStatesTable::GraphStatesTable( QWidget* parent ) :
    GraphStatesTable( GraphState(QVector<NodeState>()), parent )
{

}

GraphStatesTable::GraphStatesTable(GraphState state, QWidget* parent ) :
    QTableWidget( parent ), state( state )
{

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->setMinimumWidth(150);

    QStringList header;
    header << "Node" << "Distance" << "Previous";

    this->setColumnCount(3);
    this->setHorizontalHeaderLabels( header );
    this->horizontalHeader()->setStretchLastSection( true );

    refresh();

}

void GraphStatesTable::setState( GraphState state ) {
    this->state = state;

    refresh();
}

GraphState GraphStatesTable::getState() const {
    return state;
}



//refresh the table, by picking data from states
void GraphStatesTable::refresh() {
    QVectorIterator<NodeState> i(state.getNodes());

    this->clearContents();
    this->setRowCount( 0 );

    //iterating through states
    while( i.hasNext() ) {
        //current state
        NodeState state = i.next();

        //adding new row
        this->setRowCount( this->rowCount() + 1 );
        this->setItem( this->rowCount() - 1, 0, new QTableWidgetItem( state.getName() ) );
        this->setItem( this->rowCount() - 1, 1, new QTableWidgetItem( QString::number(state.getDistance()) ) );
        this->setItem( this->rowCount() - 1, 2, new QTableWidgetItem( state.getPreviousNodeName() ) );

    }
}
