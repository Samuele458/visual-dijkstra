#ifndef GRAPHSTATESWIDGET_H
#define GRAPHSTATESWIDGET_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "common/graphstate.h"
#include "widgets/graphstatestable.h"

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

private:

    QVector<GraphState> states;

    // --- widgets ---
    QLabel* statesTitle;
    QVBoxLayout* layout;
    GraphStatesTable* table;


};

#endif // GRAPHSTATESWIDGET_H
