#include <iostream>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif

#include "module.h"

using namespace std;

int main ()
{

    char inputFile[BUF_LEN];
    
#ifdef _WIN32
    SetConsoleOutputCP(65001); //set default Windows cmd output to UTF-8
    SetConsoleCP(65001);
#endif
#ifdef linux
    setlocale(LC_ALL, "");
#endif

    cout << "Enter input filename for sorting: ";
    cin >> inputFile;

    process((const char *)inputFile);

    return 0;
}
