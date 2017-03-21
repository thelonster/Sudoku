#include "sudoku.h"
#include <iostream>
#include <cmath>

int puzzle[9][9];   // 2D array that contains the sudoku puzzle

void initializepuzzle() {
    for (int a = 0; a < 9; ++a)
        for (int b = 0; b < 9; ++b)
            puzzle[a][b] = 0;
    puzzle[0][0] = 5;
    puzzle[0][1] = 3;
    puzzle[0][4] = 7;
    puzzle[1][0] = 6;
    puzzle[1][3] = 1;
    puzzle[1][4] = 9;
    puzzle[1][5] = 5;
    puzzle[2][1] = 9;
    puzzle[2][2] = 8;
    puzzle[2][7] = 6;
    puzzle[3][0] = 8;
    puzzle[3][4] = 6;
    puzzle[3][8] = 3;
    puzzle[4][0] = 4;
    puzzle[4][3] = 8;
    puzzle[4][5] = 3;
    puzzle[4][8] = 1;
    puzzle[5][0] = 7;
    puzzle[5][4] = 2;
    puzzle[5][8] = 6;
    puzzle[6][1] = 6;
    puzzle[6][6] = 2;
    puzzle[6][7] = 8;
    puzzle[7][3] = 4;
    puzzle[7][4] = 1;
    puzzle[7][5] = 9;
    puzzle[7][8] = 5;
    puzzle[8][4] = 8;
    puzzle[8][7] = 7;
    puzzle[8][8] = 9;
}

bool checkcolumn(int column) {
    int nums[10];    // array used to compare whether or not each number is visited
    for (int a = 0; a < 9; ++a) {
        // array has 10 indexes, 1 for each number able to enter in a 9x9 grid and 1 for zeroes
        // If a number hasn't shown up in the column yet, inc value at its pos
        if (nums[puzzle[a][column]] == 0 && puzzle[a][column] != 0) 
            nums[puzzle[a][column]]++;
        // If the spot is empty then don't do anything
        else if (puzzle[a][column] == 0);
        // If a number has occured more than once, return false. number won't work
        else
            return false;
    }
    // If the end of the loop has been reached
    return true;
}

bool checkrow(int row) {
    int nums[10];   // array used to compare whether or not each number is visited 
    for (int a = 0; a < 9; ++a) {
        // array has 10 indexes, 1 for each number able to enter in a 9x9 grid and 1 for zeroes
        // If a number hasn't shown up in the row yet, inc value at its pos
        if (nums[puzzle[row][a]] == 0 && puzzle[row][a] != 0)
            nums[puzzle[row][a]]++;
        // If empty, don't do anything
        else if (puzzle[row][a] == 0);
        // If a number shows up more than once, return false
        else
            return false;
    }
    return true;
}

bool checkinnersquare(int squareno) {
    int startpos;
    // Used to determine the starting position of the grid
    if (squareno < 3)
        startpos = 3 * squareno;
    else if (squareno < 6)
        startpos = 3 * (squareno - 3) + 27;
    else
        startpos = 3 * (squareno - 6) + 54;

    int nums[10];
    int* start = puzzle[startpos];
    for (int outer = 0; outer < 3; ++outer)
        for (int inner = 0; inner < 3; ++inner) {
            // Using a pointer to the array so that I can go through each spot in the grid with the least code possible
            if (nums[*(start + inner + (outer*9))] == 0 && *(start + inner + (outer * 9)) != 0)
                nums[*(start + inner + (outer * 9))]++;
            else if (*(start + inner + (outer * 9)) == 0);
            else
                return false;
        }
    return true;
}

int getgridno(int row, int col) {
    // I divide by 3 then multiply by 3 to lose precision, getting an answer that is
    // 0, 3, or 6. This is the row offset
    // Then I add the col / 3 to get the number of the grid
    return ((row / 3) * 3) + (col / 3);
}

void solve(int testno, int row, int col) {
    if (row == 8 && col == 8)
        return;
    if (puzzle[row][col] != 0) {
        if (testno == 9)
            return;
        else {
            if (col < 8)
                return solve(1, row, ++col);
            else
                return solve(1, ++row, 1);
        }
    } else {
        puzzle[row][col] = testno;
        if (checkrow(row) && checkcolumn(col) && checkinnersquare(getgridno(row, col))) {
            if (col < 8)
                return solve(1, row, ++col);
            else
                return solve(1, ++row, 1);
        }
        else {
            if (col < 8)
                return solve(++testno, row, ++col);
            else
                return solve(++testno, ++row, 1);
        }
    }
}

void printpuzzle() {
    std::cout << "Printing out the Sudoku Puzzle: " << std::endl;
    for (int a = 0; a < 9; ++a) {
        for (int b = 0; b < 9; ++b)
            std::cout << puzzle[a][b] << " ";
        std::cout << std::endl;
    }
}