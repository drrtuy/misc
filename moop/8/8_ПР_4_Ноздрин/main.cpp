#include <iostream>
#include <locale.h>

#include "module.h"

using namespace std;

int main ()
{

    char inputFile[BUF_LEN];
    char outputFile[BUF_LEN];
    
#ifdef _WIN32
    SetConsoleOutputCP(65001); //set default Windows cmd output to UTF-8
    SetConsoleCP(65001);
#endif
#ifdef linux
    setlocale(LC_ALL, "");
#endif

    cout << "Enter input filename: ";
    cin >> inputFile;
    cout << "Enter output filename: ";
    cin >> outputFile;

    process((const char *)inputFile, (const char *) outputFile);

    return 0;
}
