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
    
#ifdef _WIN32
    setlocale(LC_CTYPE, "Russian");
#endif
#ifdef linux
    setlocale(LC_ALL, "");
#endif

    fill(array, MAX_SIZE, 1, MAX_SIZE * MAX_SIZE);
    print(array, MAX_SIZE);
    cout << "Сумма элементов массива с нечётными индексами равна: "\
 << sumUp(array, MAX_SIZE) << endl;

    return 0;
}
