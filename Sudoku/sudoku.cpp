#include "sudoku.h"
#include <iostream>
#include <cmath>

int puzzle[9][9];   // 2D array that contains the sudoku puzzle
int immutable[9][9];// 2D array that contains 1s and 0s in positions of immutable numbers in the puzzle

//Initializes a premade puzzle
//Also initializes immutable
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

//Returns whether or not the column is valid
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

//Returns whether or not the row is valid
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

//Returns whether or not the 3x3 inner square is valid
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

//Returns the grid number 0-8
//This grid number is used to check if an inner square is 
int getgridno(int row, int col) {
    // I divide by 3 then multiply by 3 to lose precision, getting an answer that is
    // 0, 3, or 6. This is the row offset
    // Then I add the col / 3 to get the number of the grid
    return ((row / 3) * 3) + (col / 3);
}

//Function that returns whether or not the puzzle is solved yet
bool issolved() {
    for (int a = 0; a < 9; ++a) {
        //I have this for loop to check for 0's first. 
        //This is because 0's don't break check row/col/innersquare
        for (int b = 0; b < 9; ++b)
            if (puzzle[a][b] == 0)
                return false;
        if (!checkcolumn(a))
            return false;
        if (!checkrow(a))
            return false;
        if (!checkinnersquare(a))
            return false;
    }
    return true;
}

//Iterative algorithm that successfully solves Sudoku Puzzles
void itersolve(int row, int col) {
    // loop runs while the puzzle isn't solved
    while (!issolved()) {
        //Immutable is an array of 0's and 1's where 1's indicate a part of the puzzle that can't be changed
        //If we are at a pos of an immutable number, go to the next one
        if (immutable[row][col] == 1) {
            if (col < 8)
                ++col;
            else {
                ++row;
                col = 0;
            }
            //Using the continue statement to jump back to start of while loop
            continue;
        }
        else {
            int testno;
            //If the position is empty, start from beginning testing values
            if (puzzle[row][col] == 0)
                testno = 1;
            //If not, set testno to the next value
            else
                testno = puzzle[row][col] + 1;
            //This bool is to exit the for loop once a value is successfully placed in the puzzle
            bool success = false;
            for (testno; testno < 10 && !success; ++testno) {
                puzzle[row][col] = testno;
                if (checkrow(row) && checkcolumn(col) && checkinnersquare(getgridno(row, col))) {
                    if (col < 8)
                        ++col;
                    else {
                        ++row;
                        col = 0;
                    }
                    success = true;
                }
            }
            //To prevent undoing work, start again if value was successfully added
            if (success)
                continue;
            //getprevnonimmutable pos returns an int that is the numerical position in the puzzle
            //I can take this pos and get the new row and column
            int tempindex = getprevnonimmutablepos(row, col);
            int newrow = tempindex / 9;
            int newcol = tempindex % 9;
            puzzle[row][col] = 0;
            row = newrow;
            col = newcol;
        }
    }
}

//Non-functional recursive solve algorithm
void tempsolve(int row, int col) {
    printpuzzle();
    if (row == 8 && col == 8 && issolved())
        return;
    if (puzzle[row][col] != 0 && immutable[row][col] == 1) {
        if (col < 8)
            return tempsolve(row, ++col);
        else
            return tempsolve(++row, 0);
    }
    else {
        int testno;
        if (puzzle[row][col] == 0)
            testno = 1;
        else
            testno = puzzle[row][col] + 1;
        for (testno; testno <= 9; testno++) {
            //std::cout << "Row # " << row << " Col # " << col << std::endl;
            puzzle[row][col] = testno;
            if (checkrow(row) && checkcolumn(col) && checkinnersquare(getgridno(row, col))) {
                if (col < 8)
                    return tempsolve(row, ++col);
                else
                    return tempsolve(++row, 0);
            }
        }
        int tempindex = getprevnonimmutablepos(row, col);
        int newrow = tempindex / 9;
        int newcol = tempindex % 9;
        puzzle[row][col] = 0;
        tempsolve(newrow, newcol);
    }
}

//Non-functional recursive solve algorithm (FIRST ATTEMPT)
void solve(int testno, int row, int col) {
    if (row == 8 && col == 8)
        return;
    if (puzzle[row][col] != 0 && immutable[row][col] == 1) {
        if (col < 8)
            return solve(1, row, ++col);
        else
            return solve(1, ++row, 0); 
    }
    else {
        puzzle[row][col] = testno;
        //printpuzzle();
        //std::cout << "Row # " << row << " Col # " << col << std::endl;
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
            }
        }
    }
}

//Prints the puzzle
void printpuzzle() {
    std::cout << "Printing out the Sudoku Puzzle: " << std::endl;
    for (int a = 0; a < 9; ++a) {
        for (int b = 0; b < 9; ++b)
            std::cout << puzzle[a][b] << " ";
        std::cout << std::endl;
    }
}

//Finds the starting point for the algorithm
int findstartcol() {
    for (int a = 0; a < 9; ++a)
        if (puzzle[a][0] == 0)
            return a;
    return -1;
}

//Returns int position of the first previous position with a non immutable number
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