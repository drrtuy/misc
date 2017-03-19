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

void convert(int n[], int n_size, int m[], int m_size, int join[], int joinSize)
{
    int joinCurSize = 0;

    for (int i = 0; i < n_size; i++){
        if(findElement(n[i], join, joinCurSize)){
            continue;
        }
        join[joinCurSize++] = n[i];
    }

    
    for (int i = 0; i < m_size; i++){
        if(findElement(m[i], join, joinCurSize)){
            continue;
        }
        join[joinCurSize++] = m[i];
    }

}
