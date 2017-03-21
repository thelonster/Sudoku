#ifndef sudoku_h
#define sudoku_h

bool checkcolumn(int column);
bool checkrow(int row);
bool checkinnersquare(int squareno);
int getgridno(int row, int col);
void solve(int testno, int row, int col);
void printpuzzle();
void initializepuzzle();

#endif // !sudoku_h