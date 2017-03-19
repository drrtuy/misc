#ifndef H_MODULE
#define H_MODULE

#define MAX_COLS 5
#define MAX_ROWS 5

int findMax(double **input, int colInd, int rows, int cols); 
void swapCols(double **input, int src, int dst, int rows, int cols);
double **fill (int rows, int cols, int lb, int rb);
void print(double **input, int rows, int cols);
void *convert(double **input, int rows, int cols);

#endif
