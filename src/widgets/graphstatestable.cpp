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
    GraphStatesTable( QVector<GraphState>(), parent )
{

}

GraphStatesTable::GraphStatesTable( QVector<GraphState> states, QWidget* parent ) :
    QTableWidget( parent )
{

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->setMinimumWidth(200);

    QStringList header;
    header << "Node" << "Distance" << "Previous";
    qDebug() << "here";

    this->setColumnCount(3);this->setHorizontalHeaderLabels( header );



}

void GraphStatesTable::setStates( QVector<GraphState> states ) {
    this->states = states;


}

QVector<GraphState> GraphStatesTable::getStates() const {
    return states;
}

