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

#ifndef GRAPHSTATE_H
#define GRAPHSTATE_H

#include <QVector>
#include <QString>

#include "common/error.h"


class GraphStateError : public Error {
public:
    enum id {
        GENERIC,
        INVALID_ARGUMENT,

        INVALID_NODE_NAME,
        INVALID_NODE_DISTANCE
    };

    GraphStateError( id error_id = GENERIC, QString message = "" ) :
        Error( (Error::id)error_id, message ) { }

};

class NodeState {
public:
    static const int INF;

    NodeState( QString name, int distance = INF, QString previous = "" );
    NodeState( const NodeState& other );
    NodeState& operator=( const NodeState& other );
    bool operator==( const NodeState& other );
    bool operator!=( const NodeState& other );
    bool operator>( const NodeState& other );
    bool operator<( const NodeState& other );
    bool operator>=( const NodeState& other );
    bool operator<=( const NodeState& other );

    QString getName() const;
    int getDistance() const;
    QString getPreviousNodeName();

    void setName( QString name );
    void setDistance( int distance );
    void setPreviousNodeName( QString previous );

private:
    QString name;
    int distance;
    QString previous;
};

class GraphState
{
public:
    GraphState();
};

#endif // GRAPHSTATE_H
