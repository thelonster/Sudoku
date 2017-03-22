#include "sudoku.h"
#include <iostream>
#include <cmath>

int puzzle[9][9];   // 2D array that contains the sudoku puzzle
int immutable[9][9];// 2D array that contains 1s and 0s in positions of immutable numbers in the puzzle

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
    for (int a = 0; a < 9; ++a)
        for (int b = 0; b < 9; ++b)
            puzzle[a][b] != 0 ? immutable[a][b] = 1 : immutable[a][b] = 0;
}

bool checkcolumn(int column) {
    int nums[10] = { 0 };    // array that stores the number of occurences of numbers in the column
    for (int a = 0; a < 9; ++a) {
        nums[puzzle[a][column]]++;
    }
    for (int i = 1; i < 10; ++i)
        if (nums[i] > 1)
            return false;
    // Fill the nums with the values of what is in the puzzle column
    // Then if any number besides 0 occurs more than once
    // Return false, otherwise return true;
    return true;
}

bool checkrow(int row) {
    int nums[10] = { 0 };    // array that stores the number of occurences of numbers in the row
    for (int a = 0; a < 9; ++a) {
        nums[puzzle[row][a]]++;
    }
    for (int i = 1; i < 10; ++i)
        if (nums[i] > 1)
            return false;
    // Fill the nums with the values of what is in the puzzle column
    // Then if any number besides 0 occurs more than once
    // Return false, otherwise return true;
    return true;
}

bool checkinnersquare(int squareno) {
    int startrow, startcol;
    // Used to determine the starting position of the grid
    if (squareno < 3)
        startrow = 0;
    else if (squareno < 6)
        startrow = 3;
    else
        startrow = 6;
    startcol = (squareno % 3) * 3;

    int nums[10] = { 0 };
    for (int outer = 0; outer < 3; ++outer)
        for (int inner = 0; inner < 3; ++inner)
            nums[puzzle[startrow + outer][startcol + inner]]++;
    for (int a = 1; a < 10; ++a)
        if (nums[a] > 1)
            return false;
    return true;
}

int getgridno(int row, int col) {
    // I divide by 3 then multiply by 3 to lose precision, getting an answer that is
    // 0, 3, or 6. This is the row offset
    // Then I add the col / 3 to get the number of the grid
    return ((row / 3) * 3) + (col / 3);
}

void solve(int testno, int row, int col) {
    //printpuzzle();
    if (row == 8 && col == 8)
        return;
    if (puzzle[row][col] != 0) {
        if (col < 8)
            return solve(1, row, ++col);
        else
            return solve(1, ++row, 0); 
    } else {
        puzzle[row][col] = testno;
        if (checkrow(row) && checkcolumn(col) && checkinnersquare(getgridno(row, col))) {
            if (col < 8)
                return solve(1, row, ++col);
            else
                return solve(1, ++row, 0);
        }
        else {
            puzzle[row][col] = 0;
            if (testno < 9)
                return solve(++testno, row, col);
            else {
                int tempindex = getprevnonimmutablepos(row, col);
                int newrow = tempindex / 9;
                int newcol = tempindex % 9;
                int prevtestno = puzzle[newrow][newcol];
                puzzle[newrow][newcol] = 0;
                while (prevtestno == 9) {
                    tempindex = getprevnonimmutablepos(newrow, newcol);
                    newrow = tempindex / 9;
                    newcol = tempindex % 9;
                    prevtestno = puzzle[newrow][newcol];
                    puzzle[newrow][newcol] = 0;
                }
                solve(++prevtestno, newrow, newcol);

                //if (col < 8)
                //    solve(1, row, ++col);
                //else 
                //    solve(1, ++row, 0);
            }
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

int findstartcol() {
    for (int a = 0; a < 9; ++a)
        if (puzzle[a][0] == 0)
            return a;
}

int getprevnonimmutablepos(int row, int col) {
    do {
        if (col == 0 && row > 0) {
            col = 8;
            --row;
        }
        else
            --col;
    } while (immutable[row][col] != 0);
    return 9 * row + col;
}