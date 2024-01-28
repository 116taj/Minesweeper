#ifndef TILE_H
#define TILE_H
#include <QString>

class Tile
{

public:
    Tile(int=0);
    void reveal();
    bool isRevealed();
    int getValue();
    void setValue(int);
    void incrementValue();
    bool containsMine();
    bool hasFlag();
    void setFlag(bool);
    QString toString();
private:
    int underneath;
    bool revealed;
    bool flagged;
};

#endif // TILE_H
