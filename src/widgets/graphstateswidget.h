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



};

#endif // GRAPHSTATESWIDGET_H
