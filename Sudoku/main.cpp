#include "sudoku.h"

int main() {
    initializepuzzle();
    printpuzzle();
    solve(1, 0, 0);
    printpuzzle();
}