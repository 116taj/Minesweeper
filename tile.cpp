#include "tile.h"

Tile::Tile(int v)
{
    underneath = v;
    revealed = false;
    flagged = false;
}

bool Tile::containsMine(){
    if (underneath == -1)
        return true;
    return false;
}

int Tile::getValue(){
    return underneath;
}
void Tile::setValue(int v){
    underneath = v;
}

void Tile::incrementValue(){
    underneath++;
}

bool Tile::hasFlag(){
    return flagged;
}

void Tile::setFlag(bool f){
    flagged = f;
}

bool Tile::isRevealed(){
    return revealed;
}

QString Tile::toString(){
    if (flagged)
        return "F";
    else if (!revealed)
        return "\0";
    else if (underneath < 0)
        return "M";
    return QString::number(underneath);

}

void Tile::reveal(){
    revealed = true;
}
