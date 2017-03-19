#include <stdio.h>
#include <locale.h>
#include <string.h>
#ifdef linux
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif
#include "module.h"

void fill(int a[], int size, int lb, int rb);
void print(int a[], int size);
void convert(int n[], int n_size, int m[], int m_size, int join[], int joinSize);

int main ()
{
    int nArray[N_SIZE], mArray[M_SIZE], join[N_SIZE + M_SIZE];

    fill(nArray, N_SIZE, 1, N_SIZE * N_SIZE);
	
#ifdef linux
	sleep(1);
#endif
#ifdef _WIN32
	Sleep(1000);
#endif
	
    fill(mArray, M_SIZE, 1, M_SIZE * M_SIZE);
    printf("%ls\n", L"The elements of the first array");
    print(nArray, N_SIZE);
    printf("%ls\n", L"The elements of the second array");
    print(mArray, M_SIZE);

    memset((void *) &join, -1, sizeof(join[0]) * (N_SIZE + M_SIZE));

    convert(nArray, N_SIZE, mArray, M_SIZE, join, N_SIZE + M_SIZE);
    printf("%ls\n", L"Cross of the arrays.");
    print(join, N_SIZE + M_SIZE);

    return 0;
}
