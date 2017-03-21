#include "sudoku.h"

int main() {
    initializepuzzle();
    printpuzzle();
    solve(1, 0, findstartcol());
    printpuzzle();
}