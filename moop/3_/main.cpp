#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    cout << "Введите последовательность значений функции "
    << "одно значение на строку." << endl;
    cout << "Пустое значение завершает ввод и записывает результат "
    << "в файл output.txt" << endl;

    ofstream outPut("output.txt");

    if(!outPut)
    {
        cerr << "Не могу открыть поток в файл вывода." << endl;
        return 1;
    }

    string rawInput;
    double fValue;

    try
    {
        getline(cin, rawInput);
    }
    catch (...)
    {
        getline(cin, rawInput);
    }

    while ( !rawInput.empty() )
    {
        fValue = ::atof(rawInput.c_str());
        try
        {
            outPut << fValue << " ";
            getline(cin, rawInput);
        }
        catch (...)
        {
            cerr << "Не могу записать в поток вывода." << endl;
        }
    }

    outPut << endl;
    outPut.close();
    cout << "Запись завершена - проверьте output.txt." << endl;

    return 0;
}
