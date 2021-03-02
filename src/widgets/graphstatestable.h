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

#ifndef GRAPHSTATESTABLE_H
#define GRAPHSTATESTABLE_H

#include <QTableWidget>
#include <QDebug>
#include <QVector>

#include "common/graphstate.h"


class GraphStatesTable : public QTableWidget
{
    Q_OBJECT
public:

    GraphStatesTable( QWidget* parent = nullptr );
    GraphStatesTable( QVector<GraphState> states = QVector<GraphState>(), QWidget* parent = nullptr );

    void setStates( QVector<GraphState> states );
    QVector<GraphState> getStates() const;

private:
    QVector<GraphState> states;

};

#endif // GRAPHSTATESTABLE_H
