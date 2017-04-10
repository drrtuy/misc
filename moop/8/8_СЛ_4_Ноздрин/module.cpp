#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdlib.h>

#include "module.h"

using namespace std;

//
// Функция сортирует содержимое исходного файла по длине строк.
//
//in1 const char * имя input файла
//
//
void process(const char *inputFile)
{
    ifstream input;
    char str[BUF_LEN] = "";
    vector <row_desc_t> rowsDescr, sortedRowsDescr;
    vector <row_desc_t>::iterator iter, iterSorted;
    row_desc_t *curRowDescr;
    int rowsNumb = 0;

    input.open(inputFile);

    if(!input)
    {
        cout << "Could`nt open input filestream\n" << endl;
        exit(1);
    }

    do
    {
        input.getline(str, BUF_LEN); 

        curRowDescr = new row_desc_t; //для быстрого перемещения по файлу
        curRowDescr->row_number = rowsNumb;
        curRowDescr->row_length = strlen(str);
        rowsDescr.push_back(*curRowDescr);

        curRowDescr = new row_desc_t; //для сортировки по длине строки
        curRowDescr->row_number = rowsNumb++;
        curRowDescr->row_length = strlen(str);
        sortedRowsDescr.push_back(*curRowDescr);
    } while (!input.eof());

    input.close();

    sort(sortedRowsDescr.begin(), sortedRowsDescr.end(), compare);

    outputSorted("output.txt", inputFile, rowsDescr, sortedRowsDescr);
    
    cout << "output.txt contains lines of the input text sorted by length." << endl;

} 


//
// Функция для сравнения при сортировке.
//
//in1 row_desc_t левый операнд
//in2 row_desc_t правый операнд
//out bool результат сравнения
//
bool compare(row_desc_t left, row_desc_t right)
{
    return (left.row_length > right.row_length);
}

//
// Функция для вывода строк в файл по убыванию длин строк
//
//in1 const char* имя выходного файла
//in2 const char* имя входного файла
//in3 vector <row_desc_t> вектор структур
//in4 vector <row_desc_t> вектор структур, сортированных по длине
//
void outputSorted(const char *outputFile, const char *inputFile,\
 vector <row_desc_t> rowsDescr, vector <row_desc_t> sortedRowsDescr)
{
    ofstream output;
    vector <row_desc_t>::iterator iter;
    char buf[BUF_LEN];

    output.open(outputFile);

    if(!output)
    {
        cout << "Could`nt open output filestream\n" << endl;
        exit(1);
    }

    for(iter = sortedRowsDescr.begin(); iter != sortedRowsDescr.end(); iter++)
    {
        getNextLine(buf, inputFile, rowsDescr, iter->row_number); 
        output << buf << endl;
    }

    output.close();
}

//
// Функция для вывода строк в файл по убыванию длин строк
//
//in1 const char* имя выходного файла
//in2 const char* имя входного файла
//in3 vector <row_desc_t> вектор структур
//
bool getNextLine(char *buf, const char *inputFile, vector <row_desc_t> rowsDescr,\
int rowNumber)
{
    if (rowNumber > rowsDescr.size())
    {
        return false;
    }

    ifstream input(inputFile);
    int pos = 0;
    vector <row_desc_t>::iterator iter;

    for(iter = rowsDescr.begin(); iter != rowsDescr.begin()+rowNumber; iter++)
    {
        pos += (iter->row_length + ENDL_OFFSET);
    }
	
    input.seekg(pos);
    input.getline(buf, BUF_LEN);
	
    input.close();

    return true; 
}
