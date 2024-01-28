#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "multiclickbutton.h"
#include "grid.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void updateGameSize(int);
    void flag();
    void reveal();
    void incrementTimer();

private:
    void redrawGrid();
    QString timeToString();
    Ui::MainWindow *ui;
    Grid* grid;
    QTimer* mainTimer;
    bool gameStarted;
    int timeElasped;
};
#endif // MAINWINDOW_H
