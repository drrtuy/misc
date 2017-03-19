#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "module.h"

bool isLeftSide(int y, int x, int size) 
{
    return (bool) (x == 0);
}

bool isBottomLine(int y, int x, int size)
{
    return (bool) (y == size - 1);
}

bool isRightSide(int y, int x, int size)
{
    return (bool) (x == size - 1);

}

bool isTopLine(int y, int x, int size)
{
    return (bool) (y == 0);
}

bool isLeftBottom(int y, int x, int size)
{
    return (bool) ((x == 0) && (y == size - 1));
}

bool isRightTop(int y, int x, int size)
{
    return (bool) ((x == size -1) && (y == 0));
}

void moveAtLeftSide(int *y, int *x, int size, enum direction_t *direction)
{
    if ((*y % 2) == 0) {
        *y += 1; *direction = up;
    } else {
        *y -= 1; *x += 1;
    }        
}

void moveAtRightSide(int *y, int*x, int size, enum direction_t *direction)
{
    if ((size % 2) == 0) {
        if ((*y % 2) == 0) {
            *y += 1;
        } else {
            *y += 1; *x -= 1; *direction = down;
        } 
    } else {
        if ((*y % 2) == 0) {
            *y += 1; *x -= 1; *direction = down;
        } else {
            *y += 1;
        }
    }
}

void moveAtBottomLine(int *y, int*x, int size, enum direction_t *direction)
{
    if ((size % 2) == 0) {
        if ((*x % 2) == 0) {
            *x += 1; *y -= 1; *direction = up;
        } else {
            *x += 1;
        } 
    } else {
        if ((*x % 2) == 0) {
            *x += 1;
        } else {
            *x += 1; *y -= 1; *direction = up;
        }
    }
}

void moveAtTopLine(int *y, int*x, int size, enum direction_t *direction)
{
    if ((*x % 2) == 0) {
        *y += 1; *x -= 1; *direction = down;
    } else {
        *x += 1;
    }
}

void moveDiag(int *y, int*x, int size, enum direction_t *direction)
{
    if (*direction == down) {
        *y += 1; *x -= 1;
    } else {
        *y -= 1; *x += 1;
    }
}

void moveBottomLeft(int *y, int*x, int size, enum direction_t *direction)
{
    if ((size % 2) == 0) {
        *y -= 1; *x += 1; *direction = up;   
    } else {
        *x += 1;
    }
}
void moveTopRight(int *y, int*x, int size, enum direction_t *direction)
{
    if ((size % 2) == 0) {
        *y += 1;
    } else {
        *y += 1; *x -= 1; *direction = down;   
    }
}

//
// Заполнение двумерного массива int-ов змейкой.
// 
// arg1 int количество строк
// arg2 int количество колонок
// 
// out1 int** заполненный массив
//
int **fill(int rows, int cols, int lb, int rb)
{
    int i = 0, curRow = 0, curCol = 0;
    enum direction_t direction;
    int **a = NULL;

    a = (int **) malloc(sizeof(int *) * rows);    
    if (a == NULL) {
        exit(1);
    } 

    for (i = 0; i < rows; i++) {
        a[i] = (int *) malloc(sizeof(int) * cols);
        if (a[i] == NULL) {
            exit(1);
        } 
    } 

    for (i = 0; i < rows * cols; i++) {
/*        printf("%ls: %d %d %ls: %d\n", L"текущая позиция курсора: ", \
curRow, curCol, L"направление: ", direction);  
*/
        a[curRow][curCol] = i;

        if (isLeftBottom(curRow, curCol, cols)) { 
           moveBottomLeft(&curRow, &curCol, cols, &direction);
        } else if (isRightTop(curRow, curCol, cols)) {
            moveTopRight(&curRow, &curCol, cols, &direction);
        } else if (isLeftSide(curRow, curCol, cols)) { 
            moveAtLeftSide(&curRow, &curCol, cols, &direction);
        } else if (isRightSide(curRow, curCol, cols)){
            moveAtRightSide(&curRow, &curCol, cols, &direction);
        } else if (isTopLine(curRow, curCol, cols)){
            moveAtTopLine(&curRow, &curCol, cols, &direction);
        } else if (isBottomLine(curRow, curCol, cols)){
            moveAtBottomLine(&curRow, &curCol, cols, &direction); 
        } else {
            moveDiag(&curRow, &curCol, cols, &direction);
        }
    }

    return a; 
}

//
// Вывод элементов массива int-ов на консоль.
// 
// arg1 двумерный массив int-ов
// arg1 int количество строк
// arg2 int количество колонок
// 
void print(int **a, int rows, int cols)
{

    for (int i = 0; i < rows; i++) {
        for (int it = 0; it < cols; it++) {
            printf("%d\t", a[i][it]);
        }
        printf("\n");
    }
}

