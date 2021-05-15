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

#include "common/adjacencymatrix.h"

//Set the graph, and generates the matrix
AdjacencyMatrix::AdjacencyMatrix( Graph* graph ) {
    this->setGraph( graph );
}

Graph* AdjacencyMatrix::getGraph() const {
    return graph;
}

//Set the graph, and generates the matrix
void AdjacencyMatrix::setGraph( Graph* graph ) {
    this->graph = graph;

    generate();
}

//generates a matrix
void AdjacencyMatrix::generate() {
    if( graph != nullptr ) {


        //generating names
        nodes.clear();
        QVectorIterator<Node*> i(graph->getNodes());
        while(i.hasNext()) {
            nodes << i.next()->getName();
        }

        //generating matrix
        matrix.clear();
        for( int i = 0; i < nodes.size(); ++i ) {
            QVector<int> row;
            for( int j = 0; j < nodes.size(); ++j ) {
                Node* node_i = graph->getNode(nodes.at(i));
                Node* node_j = graph->getNode(nodes.at(j));

                row.push_back(node_i->getNeighbours().indexOf(node_j) == -1 ? 0 : 1 );
            }

            matrix.push_back(row);
        }

    } else {
        nodes = QStringList();
        matrix = QVector<QVector<int>>();
    }
}

QStringList AdjacencyMatrix::getNodes() const {
    return nodes;
}

QVector<QVector<int>> AdjacencyMatrix::getMatrix() const {
    return matrix;
}
