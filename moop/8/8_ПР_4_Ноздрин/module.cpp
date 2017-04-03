#include <fstream>
#include <iostream>

#include "module.h"

using namespace std;

//
// Функция пишет первый символ строки из input файла в output. Выводит только ASCII.
//
//in1 const char * имя input файла
//in2 const char * имя output файла
//
//
void process(const char *inputFile, const char *outputFile)
{
    ifstream input;
    ofstream output;
    char str[BUF_LEN] = "";


#ifdef linux
    setlocale(LC_ALL, "");
#endif

    input.open(inputFile);
    output.open(outputFile);
    
    if(!inputFile)
    {
        cout << "Could`nt open input filestream\n" << endl;
    }
                                                                                                                                                                         
    if(!outputFile)
    {
        cout << "Could`nt open output filestream\n" << endl;
    }

    do
    {
        input.getline(str, BUF_LEN);
        cout << *str << endl;
        output << str[0] << " ";
    } while (!input.eof());

    output << endl;

    input.close();
    output.close();
} 
