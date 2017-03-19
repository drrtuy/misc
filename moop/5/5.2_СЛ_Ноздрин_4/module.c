#include <stdio.h>
#include <time.h>
#include <stdlib.h>

double **fill(int rows, int cols, int lb, int rb)
{
    int i = 0;
    double **a = NULL;

    srand((unsigned int) time(0));
    a = (double **) malloc(sizeof(double *) * rows);    
    if (a == NULL) {
        exit(1);
    } 

    for (i = 0; i < rows; i++) {
        a[i] = (double *) malloc(sizeof(double) * cols);
        if (a[i] == NULL) {
            exit(1);
        } 
        for (int it = 0; it < cols; it++) {
           a[i][it] = (rb - lb) * ((float)rand()) / RAND_MAX + lb;
        }
    } 

    return a; 
}

int findMax(double **input, int colInd, int rows, int cols) 
{
    int maxInd = colInd;
    double maxVal = input[rows-1][colInd], curVal = 0.0;

    for (int i = colInd + 1; i < cols; i++) {
        if (maxVal < (curVal = input[rows-1][i])) {
            maxInd = i; maxVal =  curVal;
        }
    }

    return maxInd;
}

void swapCols(double **input, int src, int dst, int rows, int cols)
{
    double buffer = 0.0;
    for (int i = 0; i < rows; i++) {
        buffer = input[i][dst];
        input[i][dst] = input[i][src];
        input[i][src] = buffer;
    }
}

void print(double **a, int rows, int cols)
{

    for (int i = 0; i < rows; i++) {
        for (int it = 0; it < cols; it++) {
            printf("%f\t", a[i][it]);
        }
        printf("\n");
    }
}

void *convert(double **input, int rows, int cols)
{
    int maxInd = 0;

    for (int i = 0; i < cols; i++) {
        maxInd = findMax(input, i, rows, cols);
        swapCols(input, maxInd, i, rows, cols);
    } 
     
    return input;
}

