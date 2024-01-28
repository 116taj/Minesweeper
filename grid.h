#ifndef GRID_H
#define GRID_H
#include "tile.h"
#include <QRandomGenerator>
#include <QSet>

class Grid
{

public:
    Grid(int row,int col,int mine);
    ~Grid();
    int getRows();
    int getColumns();
    int getMines();
    int getFlags();
    void print();
    QString getTileContents(int,int);
    void reveal(int);
    void revealTile(int);
    void revealGrid();
    void flagTile(int);
    bool checkLose();
    bool checkWin();
private:
    void generateMinePositions();
    void generateNumbers();
    void placeMine(int);
    bool hasAdjacentMines(int);
    void lose();
    Tile** grid;
    int mineCount;
    int flagCount;
    int* minePositions;
    int row;
    int col;
    int gameState;
};

#endif // GRID_H
