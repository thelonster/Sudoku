#ifndef sudoku_h
#define sudoku_h

/*Initializes a premade puzzle*/
void initializepuzzle();

/*Returns whether or not the column is valid*/
bool checkcolumn(int column);

/*Returns whether or not the row is valid*/
bool checkrow(int row);

/*Returns whether or not the 3x3 inner square is valid*/
bool checkinnersquare(int squareno);

/*Function that returns whether or not the puzzle is solved yet*/
int getgridno(int row, int col);

/*Iterative algorithm that successfully solves Sudoku Puzzles*/
void itersolve(int row, int col);

/*Non-functional recursive solve algorithm*/
void tempsolve(int row, int col);

/*Non-functional recursive solve algorithm (FIRST ATTEMPT)*/
void solve(int testno, int row, int col);

/*Prints the puzzle*/
void printpuzzle();

/*Finds the starting point for the algorithm*/
int findstartcol();

/*Returns int position of the first previous position with a non immutable number*/
int getprevnonimmutablepos(int row, int col);

#endif // !sudoku_h