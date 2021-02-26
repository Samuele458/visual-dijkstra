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

#ifndef ERROR_H
#define ERROR_H
#include <QString>

class Error
{

public:
    enum id {
        GENERIC,
        INVALID_ARGUMENT,
    };

    Error( id error_id = GENERIC, QString message = "" );

    id getId() const;
    void setId( id error_id );
    QString getMessage() const;
    void setMessage( QString message );


private:
    QString message;
    id error_id;

};

#endif // ERROR_H
