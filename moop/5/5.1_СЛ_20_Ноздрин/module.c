#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "module.h"

enum bool findElement(int el, int array[], int size)
{
    for (int i = 0; i < size; i++){
        if (array[i] == el)
            return true;
    }

    return false;
} 

void fill(int a[], int size, int lb, int rb)
{
    srand((unsigned int) time(NULL));
    for (int i = 0; i < size; i++) {
        a[i] = (rb - lb) * ((float)rand()) / RAND_MAX + lb;
    }
}

void print(int a[], int size)
{
    for (int i = 0; i < size; i++) {
        if(a[i] != -1) {
            printf("%d\n", a[i]);
        }
    }
}

void convert(int n[], int n_size, int result[])
{
    int resultCurSize = 0;

    for (int i = 0; i < n_size; i++){
        if(findElement(n[i], result, resultCurSize)){
            continue;
        }
        result[resultCurSize++] = n[i];
    }

}
