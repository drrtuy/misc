#include <iostream>
#include <time.h>
#include <stdlib.h>

using std::cout;

void fill(double a[], int size, int lb, int rb)
{
     int i;
     srand((unsigned int) time(0));
     for (i = 0; i < size; i++) {
         a[i] = (rb - lb) * ((float)rand()) / RAND_MAX + lb;
     }
}

void print(double a[], int size)
{
    for (int i; i < size; i++) {
        cout << i << " " << a[i];
    }
}

int sumUp(double array[], int size)
{
    double result = 0.0;

    for (int i = 0; i < size; i += 2){
            result += array[i];
    }

    return result;
}
