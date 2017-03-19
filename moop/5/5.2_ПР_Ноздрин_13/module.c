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

double calcAvg(double *input, int cols)
{
    double avg = 0.0;
    for (int i = 0; i < cols; i++) {
        avg += input[i];
    }
    //printf("%f\n", avg/cols);
    
    return avg / cols;
}

void print(double **a, int rows, int cols)
{
    double avg = 0.0;

    for (int i = 0; i < rows; i++) {
        avg = calcAvg(a[i], cols);        
        for (int it = 0; it < cols; it++) {
            printf("%f\t", a[i][it]);
        }
        printf("\tavg: %f", avg);
        printf("\n");
    }
}

double **convert(double **input, int rows, int cols)
{
    double avg = 0.0;
    double **result = NULL;

    result = (double **) malloc(sizeof(double *) * rows);    
    if (result == NULL) {
        exit(1);
    } 

    for (int i = 0; i < rows; i++) {
        avg = calcAvg(input[i], cols);
        result[i] = (double *) malloc(sizeof(double) * cols);
        for (int it = 0; it < cols; it++) {
            result[i][it] = input[i][it] - avg;
        }
    } 
     
    return result;
}

