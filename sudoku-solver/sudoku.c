#include <stdio.h>

#define UNASSIGNED 0
#define N 9

void printGrid(int grid[N][N]);
int solveGrid(int grid[N][N]);
int findUnassigned(int grid[N][N], int *r, int *c);

int isValidInRow(int grid[N][N], int number, int r);
int isValidInColumn(int grid[N][N], int number, int r);
int isValidInBox(int grid[N][N], int number, int rowStart, int colStart);
int isValid(int grid[N][N], int number, int r, int c);

int main(int argc, char *argv[]) {
  // clang-format off
  int grid[N][N] = {{1, 0, 0, 4, 9, 0, 6, 8, 3},
                    {3, 6, 5, 0, 0, 0, 0, 0, 7},
                    {0, 8, 0, 0, 0, 7, 1, 0, 2},
                    {0, 0, 0, 0, 4, 9, 7, 0, 8},
                    {0, 0, 3, 0, 7, 8, 9, 6, 5},
                    {0, 0, 0, 6, 5, 0, 2, 0, 0},
                    {0, 0, 6, 9, 0, 0, 0, 1, 0},
                    {8, 0, 0, 0, 3, 0, 0, 0, 0},
                    {9, 0, 2, 5, 1, 0, 0, 7, 6}};

  if(solveGrid(grid)) {
    printGrid(grid);
  } else {
    printf("Failed to solve sudoku.\n");
  }
  return 0;
}


int solveGrid(int grid[N][N])
{
  int r, c;
  if(findUnassigned(grid, &r, &c)) {
    for(int n = 1; n <= 9; n++) {
      if(isValid(grid, n, r, c)) {
        grid[r][c] = n;

        // i wish her love for me had recurssion
        if(solveGrid(grid)) return 1;
        grid[r][c] = UNASSIGNED;
      }
    }
  } else {
    return 1;
  }

  return 0;
}


void printGrid(int grid[N][N])
{
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < N; c++) {
      printf(" %d ", grid[r][c]);
    }
    printf("\n");
  }
}

int findUnassigned(int grid[N][N], int *r, int *c)
{
  for(*r = 0; *r < N; (*r)++) {
    for(*c = 0; *c < N; (*c)++) {
      if(grid[*r][*c] == UNASSIGNED) {
        return 1;
      }
    }
  }
  return 0;
}


int isValidInRow(int grid[N][N], int number, int r)
{
  for(int c = 0; c < N; c++) {
    if(grid[r][c] == number) {
      return 0;
    }
  }
  return 1;
}

int isValidInColumn(int grid[N][N], int number, int c)
{
  for(int r = 0; r < N; r++) {
    if(grid[r][c] == number) {
      return 0;
    }
  }
  return 1;
}

int isValidInBox(int grid[N][N], int number, int rowStart, int colStart)
{
  for(int r = 0; r < 3; r++) {
    for(int c = 0; c < 3; c++) {
      if(grid[rowStart + r][colStart + c] == number) {
        return 0;
      }
    }
  }
  return 1;
}


int isValid(int grid[N][N], int number, int r, int c) {
  if(grid[r][c] == UNASSIGNED && isValidInRow(grid, number, r) && isValidInColumn(grid, number, c) && isValidInBox(grid, number, r - r % 3, c - c % 3)) return 1;
  return 0;
}
