#ifndef MATRIXDIALOG_H
#define MATRIXDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QFont>
#include <QFileDialog>
#include <QTextStream>

#include "common/adjacencymatrix.h"
#include "widgets/graph.h"


class MatrixTableWidget : public QTableWidget, public AdjacencyMatrix {
public:
    MatrixTableWidget( Graph* graph, QWidget* parent = nullptr );

    void paintEvent(QPaintEvent *) override;

};


class MatrixDialog : public QDialog {
    Q_OBJECT

public:
    MatrixDialog( Graph* graph, QWidget* parent = nullptr );



private slots:
    void closeButtonClicked();
    void csvExportButtonClicked();

private:

    QVBoxLayout* mainLayout;

    MatrixTableWidget* matrixTable;
    QHBoxLayout* buttons;

    QPushButton* closeButton;
    QPushButton* csvExportButton;



};

#endif
