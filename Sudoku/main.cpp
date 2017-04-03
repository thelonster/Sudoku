#include "sudoku.h"

int main() {
    initializepuzzle();
    printpuzzle();
    tempsolve(0, findstartcol());
    printpuzzle();
}