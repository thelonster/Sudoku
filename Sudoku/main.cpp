#include "sudoku.h"

int main() {
    initializepuzzle();
    printpuzzle();
    itersolve(0, findstartcol());
    printpuzzle();
}