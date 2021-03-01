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

#include "graphstate.h"


const int NodeState::INF = -1;


NodeState::NodeState( QString name, int distance, QString previous ) {
    this->name = name;
    this->distance = distance;
    this->previous = previous;
}

NodeState::NodeState( const NodeState& other ) {
    name = other.name;
    distance = other.distance;
    previous = other.previous;
}

NodeState& NodeState::operator=( const NodeState& other ) {
    name = other.name;
    distance = other.distance;
    previous = other.previous;

    return *this;
}

bool NodeState::operator==( const NodeState& other ) {
    return distance == other.distance;
}

bool NodeState::operator!=( const NodeState& other ) {
    return !operator==( other );
}

bool NodeState::operator>( const NodeState& other ) {
    return distance > other.distance;
}

bool NodeState::operator<( const NodeState& other ) {
    return distance < other.distance;
}

bool NodeState::operator>=( const NodeState& other ) {
    return distance >= other.distance;
}

bool NodeState::operator<=( const NodeState& other ) {
    return distance <= other.distance;
}

QString NodeState::getName() const {
    return this->name;
}

int NodeState::getDistance() const {
    return this->distance;
}

QString NodeState::getPreviousNodeName() {
    return this->previous;
}

void NodeState::setName( QString name ) {

    //name could not be empty
    if( name == "" ) {
        throw GraphStateError( GraphStateError::INVALID_NODE_NAME );
    } else {
        this->name = name;
    }
}

void NodeState::setDistance( int distance ) {
    //only distance > 0 or equal to INF is allowed
    if( distance != INF && distance < 0 ) {
        throw GraphStateError( GraphStateError::INVALID_NODE_DISTANCE );
    } else {
        this->distance = distance;
    }
}

void NodeState::setPreviousNodeName( QString previous ) {
    this->previous = previous;
}
