#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>

#include "module.h"

void fill(int a[], int size, int lb, int rb);
void print(int a[], int size);
void convert(int n[], int n_size, int result[]);

int main ()
{
    int nArray[N_SIZE], result[N_SIZE];
    memset((void *) &result, -1, sizeof(result[0]) * (N_SIZE));

#ifdef _WIN32
    setlocale(LC_CTYPE, "Russian"); 
#endif
#ifdef linux
    setlocale(LC_ALL, "");
#endif

    fill(nArray, N_SIZE, 1, N_SIZE * N_SIZE);

    printf("%ls\n", L"Элементы массива N");
    print(nArray, N_SIZE);

    convert(nArray, N_SIZE, result);
    printf("%ls\n", L"Множество чисел из N");
    print(result, N_SIZE);

    return 0;
}
