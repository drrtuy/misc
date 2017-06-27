#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef linux
#include <unistd.h>
#endif
#include <math.h>

#include "rational.h"

using namespace std;

// _nom - int
// _denom int

//
// Def конструктор
// 
Rational::Rational()
{
    _nom = 0;
    _denom = 0;    
}

//
// Конструктор инициализации
// in1 int числитель  
// in2 int знаменатель. Constraint не равен 0.
//
Rational::Rational(int nom, int denom)
{
    _nom = nom;
    if (!denom){
        _denom = 0;    
        _nom = 0;
        cout << "Rational::Rational() You can't use 0 as denominator value" << endl;
    } else {
        _denom = denom;
    }
}

//
// Конструктор копирования
// in1 &Rational
//
Rational::Rational(const Rational &Operand)
{
    _nom = Operand._nom;
    _denom = Operand._denom;
}

//
// Деструктор. Просто деструктор
//
Rational::~Rational()
{
    _nom = 0;
    _denom = 0;    
}

//
// Ф-ия выводит в cout значение рационального числа.
//
void Rational::outPut()
{
    cout << _nom << "/" << _denom << endl; 
}

//
// Ф-ия возвращает числитель.
// out int числитель
int Rational::getNom()
{
    return _nom;
}

//
// Ф-ия возвращает знаменатель.
// out int знаменатель
int Rational::getDenom()
{
    return _denom;
}

//
// Операция сравнения двух чисел между собой:
// this > Operand
// in1 правый операнд
// out результат сравнения
// 
bool Rational::operator>(const Rational &Operand)
{
    double diff = _nom/_denom-Operand._nom/Operand._denom;
    return (diff>0);
}

//
// Функция возвращает поток со строчным представлением рационального числа.
//
std::ostream &operator<<(ostream& stream, const Rational &Operand)
{
    char *result = new char[MAX_LEN+1];
    result[MAX_LEN] = '\0';

    snprintf(result, MAX_LEN+1, "%d/%d", Operand._nom, Operand._denom);

    stream << result;
    return stream;
}
