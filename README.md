# Minesweeper

Minesweeper for desktop, written in C++ with Qt. January 2024.

Standard rules. Left click uncovers a tile, right click flags one. Clear every
tile that isn't a mine and you win. Uncovering a tile with nothing around it
opens up the empty area next to it. The toolbar shows the mine count, how many
flags you have placed, and a timer that starts on your first click.

Three board sizes in the dropdown:

| Size | Mines |
| --- | --- |
| 5x5 | 5 |
| 8x8 | 15 |
| 10x10 | 10 |

## Building

Needs Qt 5.14 or newer.

```sh
qmake Minesweeper.pro
make
./Minesweeper
```

Or open `Minesweeper.pro` in Qt Creator.

## Repository layout

```
main.cpp             Entry point
mainwindow.*         Window, toolbar, timer, redrawing the grid
grid.*               Board, mines, reveal and flag rules, win and lose checks
tile.*               One tile: what is under it, revealed, flagged
multiclickbutton.*   QPushButton that also reports right clicks
mainwindow.ui        Qt Designer layout
```

## Future work

- Mines are placed before the first click, so your first tile can be a mine.
- Three preset sizes only. Custom rows, columns and mine count would be better.
- Nothing is saved between runs, so there are no best times.
