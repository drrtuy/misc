#include <locale.h>
#include <time.h>
#include <stdio.h>

#include "module.h"

int main ()
{
    double **array = NULL;
     
#ifdef _WIN32
	SetConsoleOutputCP(65001); //set default Windows cmd output to UTF-8
#endif
#ifdef linux
    setlocale(LC_ALL, "");
#endif

    array = fill(MAX_ROWS, MAX_COLS, 1, MAX_ROWS * MAX_ROWS);

#ifdef _WIN32
    printf("%s\n", "Исходная матрица: ");
#endif
#ifdef linux
    printf("%ls\n", L"Исходная матрица: ");
#endif
    print(array, MAX_ROWS, MAX_COLS);
#ifdef _WIN32
    printf("%s\n", "Преобразованная матрица: ");
#endif
#ifdef linux
    printf("%ls\n", L"Преобразованная матрица: ");
#endif
    convert(array, MAX_ROWS, MAX_COLS);
    print(array, MAX_ROWS, MAX_COLS);

    return 0;
}
