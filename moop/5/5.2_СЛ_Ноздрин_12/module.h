#ifndef H_MODULE
#define H_MODULE

#include <stdbool.h>

#define MAX_COLS 5
#define MAX_ROWS 5

enum direction_t {up, down};

int **fill (int rows, int cols, int lb, int rb);
void print(int **input, int rows, int cols);

bool isLeftSide(int y, int x, int size);
bool isBottomLine(int y, int x, int size);
bool isRightSide(int y, int x, int size);
bool isTopLine(int y, int x, int size);
bool isLeftBottom(int y, int x, int size);
bool isRightTop(int y, int x, int size);

void moveAtLeftSide(int *y, int*x, int size, enum direction_t *direction);
void moveAtRightSide(int *y, int*x, int size, enum direction_t *direction);
void moveAtBottomLine(int *y, int*x, int size, enum direction_t *direction);
void moveAtTopLine(int *y, int*x, int size, enum direction_t *direction);
void moveDiag(int *y, int*x, int size, enum direction_t *direction);
void moveBottomLeft(int *y, int*x, int size, enum direction_t *direction);
void moveTopRight(int *y, int*x, int size, enum direction_t *direction);
#endif
