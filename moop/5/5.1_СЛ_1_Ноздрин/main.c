#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>

#include "module.h"

void fill(int a[], int size, int lb, int rb);
void print(int a[], int size);
void convert(int n[], int n_size, int m[], int m_size, int join[], int joinSize);

int main ()
{
    int nArray[N_SIZE], mArray[M_SIZE], join[N_SIZE + M_SIZE];

#ifdef _WIN32
    setlocale(LC_CTYPE, "Russian");
#endif
#ifdef linux                                                                                                                                                             
    setlocale(LC_ALL, "");
#endif

    fill(nArray, N_SIZE, 1, N_SIZE * N_SIZE);
    sleep(1);
    fill(mArray, M_SIZE, 1, M_SIZE * M_SIZE);
    printf("%ls\n", L"Элементы массива N");
    print(nArray, N_SIZE);
    printf("%ls\n", L"Элементы массива M");
    print(mArray, M_SIZE);

    memset((void *) &join, -1, sizeof(join[0]) * (N_SIZE + M_SIZE));

    convert(nArray, N_SIZE, mArray, M_SIZE, join, N_SIZE + M_SIZE);
    printf("%ls\n", L"Объединение массивов N и M");
    print(join, N_SIZE + M_SIZE);

    return 0;
}
