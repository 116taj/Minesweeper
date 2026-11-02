# Minesweeper

A desktop version of Minesweeper, written in C++ with Qt. Personal project from
January 2024.

The rules are the standard ones. Every tile hides either a mine or a number
saying how many mines touch it. Left click uncovers a tile, right click puts a
flag on one you believe is a mine, and uncovering every tile that is not a mine
wins the game. Uncovering a tile with no mines around it opens the whole empty
area next to it in one move, so the board unfolds in patches rather than tile by
tile. The toolbar keeps a mine count, a flag count, and a timer that starts on
your first click.

Three board sizes are selectable from the toolbar:

| Size | Mines |
| --- | --- |
| 5x5 | 5 |
| 8x8 | 15 |
| 10x10 | 10 |

## Building

Requires Qt 5.14 or newer and a C++ compiler.

```sh
qmake Minesweeper.pro
make
./Minesweeper
```

Or open `Minesweeper.pro` in Qt Creator and build from there.

## Repository layout

```
main.cpp             Entry point
mainwindow.*         Window, toolbar, timer, and grid redrawing
grid.*               Board state, mine placement, reveal and flag rules, win and lose checks
tile.*               One tile: what is under it, whether it is revealed or flagged
multiclickbutton.*   QPushButton that reports right clicks as well as left ones
mainwindow.ui        Qt Designer layout for the window
```

## Future work

- Mines are placed before the first click, so the first tile you open can be a
  mine. Placing them after the opening move would fix that.
- Board sizes are three fixed presets. A custom row, column, and mine count
  would be more useful.
- Nothing is saved between runs, so there are no best times.
