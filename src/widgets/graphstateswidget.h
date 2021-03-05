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

#ifndef GRAPHSTATESWIDGET_H
#define GRAPHSTATESWIDGET_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QResizeEvent>
#include <QScrollArea>
#include <QSplitter>

#include "common/graphstate.h"
#include "widgets/graphstatestable.h"
#include "widgets/graphpathfinderview.h"

class GraphPathfinderView;

class GraphStatesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphStatesWidget(QWidget *parent = nullptr);

    QVector<GraphState> getStates() const;
    void setStates( QVector<GraphState> states );

    void addState( GraphState state );

    void clearStates();

    void refresh();

    void resizeEvent(QResizeEvent *event) override;

    //apply state
    void applyState( int pos );

    void setGraphPathfinderView( GraphPathfinderView* view );
    GraphPathfinderView* getGraphPathfinderView() const;

protected slots:
    void state_button_clicked();

private:

    QVector<GraphState> states;

    // --- widgets ---
    QLabel* statesTitle;
    QVBoxLayout* layout;
    GraphStatesTable* table;
    QWidget* grid;
    QGridLayout* statesGrid;
    QVector<QPushButton*> statesButtons;
    QSplitter* splitter;
    QScrollArea* buttonsArea;

    GraphPathfinderView* graphView;

};

#endif // GRAPHSTATESWIDGET_H
