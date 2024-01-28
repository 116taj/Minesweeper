#include "grid.h"
#include <QTextStream>
Grid::Grid(int r, int c, int m)
{
    row = r;
    col = c;
    mineCount = m;
    flagCount = m;
    gameState = 0;
    minePositions = new int[mineCount];
    grid = new Tile*[row*col];
    for (int i = 0; i < row*col; i++){
      grid[i] = new Tile();
    }
    generateMinePositions();
    generateNumbers();
}

Grid::~Grid(){
    delete[] minePositions;
    for (int i = 0; i < row*col; i++){
        delete grid[i];
    }
    delete[] grid;
}

void Grid::generateMinePositions(){
    QRandomGenerator gen = QRandomGenerator::securelySeeded();
    QSet<int> set;
    while (set.size() < mineCount){
        int random = gen.bounded(row*col);
        set.insert(random);
    }
    int i = 0;
    for (int random: set){
        placeMine(random);
        minePositions[i] = random;
        i++;
        QTextStream out(stdout);
        out<<random<<Qt::endl;
    }
}
void Grid::placeMine(int pos){
    grid[pos]->setValue(-1);
}

void Grid::generateNumbers(){
    for (int i = 0; i < mineCount; i++){
        int mineIndex = minePositions[i];
        int mineRow = mineIndex/col;
        int mineCol = mineIndex%col;
        for (int j = -1; j < 2; j++){
            for (int k = -1; k < 2; k++){
                if (mineRow + j < row && mineRow + j >= 0 && mineCol + k < col && mineCol + k >= 0){
                    if (!grid[(mineRow+j)*col+mineCol+k]->containsMine())
                        grid[(mineRow+j)*col+mineCol+k]->incrementValue();
                }
            }
        }
    }
}

void Grid::print(){
    QTextStream out(stdout);
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (grid[i*col+j]->containsMine())
                out<<"*";
            else
                out<<grid[i*col+j]->getValue();
        }
        out<<"\n";
    }
}

QString Grid::getTileContents(int r, int c){
    return grid[r*col+c]->toString();
}

void Grid::reveal(int i){
    if (grid[i]->hasFlag())
        return;
    if (grid[i]->containsMine())
        lose();
    if (grid[i]->isRevealed())
        return;
    revealTile(i);
    if (hasAdjacentMines(i))
        return;
    int tileRow = i/col;
    int tileCol = i%col;
    for (int j = -1; j < 2; j++){
        for (int k = -1; k < 2; k++){
            if (tileRow + j < row && tileRow + j >= 0 && tileCol + k < col && tileCol + k >= 0){
                if (!(j == 0 && k == 0))
                    reveal((tileRow+j)*col+tileCol+k);
            }
        }
    }
}

bool Grid::hasAdjacentMines(int i){
    int tileRow = i/col;
    int tileCol = i%col;
    for (int j = -1; j < 2; j++){
        for (int k = -1; k < 2; k++){
            if (tileRow + j < row && tileRow + j >= 0 && tileCol + k < col && tileCol + k >= 0){
                if (grid[(tileRow+j)*col+tileCol+k]->containsMine() && !(j == 0 && k == 0))
                    return true;
            }
        }
    }
    return false;
}
void Grid::revealTile(int i){
    grid[i]->reveal();
}

void Grid::revealGrid(){
    for (int i = 0; i < row*col; i++){
        revealTile(i);
    }
}
int Grid::getRows(){
    return row;
}

int Grid::getColumns(){
    return col;
}

int Grid::getMines(){
    return mineCount;
}

int Grid::getFlags(){
    return flagCount;
}
void Grid::flagTile(int i){
    if (grid[i]->isRevealed())
        return;
    if (grid[i]->hasFlag()){
        grid[i]->setFlag(false);
        flagCount++;
    } else if (flagCount > 0){
        grid[i]->setFlag(true);
        flagCount--;
    }
}

void Grid::lose(){
    revealGrid();
    gameState = -1;
}

bool Grid::checkWin(){
    int count = 0;
    for (int i = 0; i < row*col; i++){
        if (!grid[i]->containsMine() && grid[i]->isRevealed())
            count++;
    }
    if (count == row*col-mineCount){
        gameState = 1;
        return true;
    }
    return false;
}


bool Grid::checkLose(){
    if (gameState == -1)
        return true;
    return false;
}
