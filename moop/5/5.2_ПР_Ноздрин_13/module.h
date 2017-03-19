#ifndef H_MODULE
#define MODULE

#include <stdbool.h>

#define MAX_COLS 5
#define MAX_ROWS 5

double **fill (int rows, int cols, int lb, int rb);
void print(double **input, int rows, int cols);
double **convert(double **input, int rows, int cols);
double calcAvg(double *input, int cols);

#endif
