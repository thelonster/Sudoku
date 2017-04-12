#include "sudoku.h"

int oldmain() {
    initializepuzzle();
    printpuzzle();
    itersolve(0, findstartcol());
    printpuzzle();
}