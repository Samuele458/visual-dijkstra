#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow() {};
private:

    QToolBar* toolbar;

    QGraphicsView* editorView;
};

#endif
