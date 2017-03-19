#include <locale.h>
#include <time.h>
#include <stdio.h>

#include "module.h"

int main ()
{
    double **array = NULL, **result = NULL;
     
#ifdef _WIN32
    //setlocale(LC_CTYPE, "Russian");
	SetConsoleOutputCP(65001);
#endif
#ifdef linux
    setlocale(LC_ALL, "");
#endif

    array = fill(MAX_ROWS, MAX_COLS, 1, MAX_ROWS * MAX_ROWS);
//    printf("%f\n", **array);
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
    result = convert(array, MAX_ROWS, MAX_COLS);
    print(result, MAX_ROWS, MAX_COLS);

    return 0;
}
