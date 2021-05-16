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

#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

#include <QVector>
#include <QStringList>

#include "widgets/graph.h"

/*
 *  Date:           15 / 05 / 2021
 *  Description:    Create the Adjacency Matrix of a given graph
 */
class AdjacencyMatrix {
public:

    //Set the graph, and generates the matrix
    AdjacencyMatrix( Graph* graph );

    Graph* getGraph() const;

    //Set the graph, and generates the matrix
    void setGraph( Graph* graph );

    //generates a matrix
    void generate( );

    QStringList getNodes() const;
    QVector<QVector<int>> getMatrix() const;



private:
    Graph* graph;

    QStringList nodes;
    QVector<QVector<int>> matrix;
};

#endif
