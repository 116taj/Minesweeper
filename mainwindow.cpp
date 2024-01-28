#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->game->setSpacing(0);
    ui->game->setContentsMargins(0,0,0,0);
    grid = 0;
    gameStarted = false;
    timeElasped = 0;
    mainTimer = new QTimer(this);
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(incrementTimer()));
    connect(ui->sizeSelector,SIGNAL(currentIndexChanged(int)),this,SLOT(updateGameSize(int)));
    int curr = ui->sizeSelector->currentIndex();
    updateGameSize(curr);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete grid;
    delete mainTimer;
}

void MainWindow::updateGameSize(int index){
    delete grid;
    QLayoutItem* item;
    while ((item = ui->game->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }
    if (index == 0) {
        grid = new Grid(5,5,5);
    } else if (index == 1) {
        grid = new Grid(8,8,15);
    } else {
        grid = new Grid(10,10,10);
    }
    redrawGrid();
}

void MainWindow::flag(){
    if (!gameStarted){
        mainTimer->start(1000);
        gameStarted = true;
    }
    MultiClickButton* mc = qobject_cast<MultiClickButton*>(QObject::sender());
    grid->flagTile(mc->getID());
    redrawGrid();
}

void MainWindow::reveal(){
    if (!gameStarted){
        mainTimer->start(1000);
        gameStarted = true;
    }
    MultiClickButton* mc = qobject_cast<MultiClickButton*>(QObject::sender());
    grid->reveal(mc->getID());
    redrawGrid();
}
void MainWindow::redrawGrid(){
    ui->flagLabel->setText("Flags: "+QString::number(grid->getFlags()));
    ui->mineLabel->setText("Mines: "+QString::number(grid->getMines()));
    if (grid->checkLose()){
       ui->mineLabel->setText("you lost");
    } else if (grid->checkWin()){
       ui->mineLabel->setText("you won");
    }
    for (int i = 0; i < grid->getRows(); i++){
        for (int j = 0; j < grid->getColumns(); j++){
            QString v = grid->getTileContents(i,j);
            MultiClickButton* button = new MultiClickButton(this,grid->getColumns()*i+j);
            connect(button,SIGNAL(clicked()),this,SLOT(reveal()));
            connect(button,SIGNAL(rightClicked()),this,SLOT(flag()));
            button->setText(v);
            button->setFixedSize(660/grid->getRows(),660/grid->getRows());
            ui->game->addWidget(button,i,j);
        }
    }
}
void MainWindow::incrementTimer(){
    timeElasped++;
    ui->timeLabel->setText(timeToString());
}

QString MainWindow::timeToString(){
    int minutes = timeElasped/60;
    int seconds = timeElasped%60;
    if (seconds < 10 && minutes < 10)
        return "0"+QString::number(minutes)+":0"+QString::number(seconds);
    else if (minutes < 10)
        return "0"+QString::number(minutes)+":"+QString::number(seconds);
    else if (seconds < 10)
        return QString::number(minutes)+":0"+QString::number(seconds);
    return QString::number(minutes)+":"+QString::number(seconds);
}
