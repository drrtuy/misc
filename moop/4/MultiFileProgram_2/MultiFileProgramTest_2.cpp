#include <clocale>
#include <iostream>
#include "MultiFileProgram_2.h"

using  std::cout;
using  std::cin;
using  std::endl;


int main() 
{
    float a = 0.0, b = 0.0, c = 0.0, d = 0.0;

    setlocale(LC_ALL, ""); 
    cout << "Введите 2 float-а для задания размеров сторон 1ой фигуры" << endl;
    cin >> a;
    cin >> b;
    cout << "Введите 2 float-а для задания размеров сторон 2ой фигуры" << endl;
    cin >> c;
    cin >> d;
    cout << a << " " << d << endl;       

    cout << "Прямоугольник со сторонами: " << a << " и " << b;
    if (isEmbedded(GetMinMax(a, b), GetMinMax(c, d))) {
        cout << " можно ";
    } else {
        cout << " нельзя ";
    }
    cout << "поместить в прямоугольник со сторонами: " << c << " и " << d << endl;
    return 0;

}
