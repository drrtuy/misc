#include <locale.h>
#include <time.h>
#include <iostream>

#include "module.h"

using std::cout;
using std::endl;

void fill(double a[], int size, int lb, int rb);
void print(double a[], int size);
int sumUp(double a[], int size);

int main ()
{
    double array[MAX_SIZE];

    fill(array, MAX_SIZE, 1, MAX_SIZE * MAX_SIZE);
    print(array, MAX_SIZE);
    cout << "The sum of the elements with odd indices of the array: "\
 << sumUp(array, MAX_SIZE) << endl;

    return 0;
}
