#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "dec.h"

//private:
//    char * _digits;
//    int _length;        

using namespace std;

//
// Инициализируем экземпляр, не указывая значения.
// in1 int длина строки для хранения цифр числа.
//
void Dec::Init(int length)
{
    if (length < MAX_LENGTH)
    {
        _digits = new char[length + 1];
        _digits[length] = '\0';
        _length = length;
    } else {
        cout << "Too big Dec" << endl;
        abort();
    }
}

//
// Инициализируем экземпляр, указывая значения.
// in1 int длина строки для хранения цифр числа.
// in2 const char* строка из цифр числа
//
void Dec::Create(int length, const char *digits)
{
    if (length < MAX_LENGTH)
    {
        _digits = new char[length + 1];
        strncpy(_digits, digits, length);
        _digits[length] = '\0';
    } else {
        cout << "Too big Dec" << endl;
        abort();
    }
    _length = length;
    
}

char *Dec::getDigits()
{
    return _digits;
}

int Dec::getLength()
{
    return _length;
}

//
// Ф-ия возвращает строку из цифр числа в превычной форме(слева старший разряд).
// out char* строка
//
char *Dec::outPut()
{
    char *result = new char[_length + 1];
    result[_length] = '\0';
    char *resDigitsCur = result;
    char *_digitsCur = _digits + _length - 1;

    while(_digitsCur != _digits - 1)
    {
        *resDigitsCur = *_digitsCur;
    //    cout << "src digit: " << *_digitsCur << " dst digit: " << *resDigitsCur << endl;
        resDigitsCur++; _digitsCur--;
    }

    return result;
}

//
// Функция сравнивает длину двух Dec, возвращая ссылку на Dec с бОльшей длиной 
// строки цифр числа
// 
// out Dec& ссылка на Dec
//
Dec Dec::_getLongest( const Dec &Operand)
{
    if (this->_length > Operand._length)
        return *this;
    return Operand;
}

Dec Dec::_getShortest( const Dec &Operand)
{
    if (this->_length > Operand._length)
        return *this;
    return Operand;
}

Dec Dec::Add(const Dec &Operand)
{
    Dec Longest = *this, Shortest = Operand, Result;
    int intBuf = 0, ResultLength = 0;
    char chBuf[2], transfer = Z;
    char *resultDigits = new char[Longest._length + 2];
    
    Longest = this->_getLongest(Operand);
    Shortest = this->_getShortest(Operand);


    char *curCurLong = Longest._digits;
    char *curCurShort = Shortest._digits;
    char *curCurRes = resultDigits;

    //cout << " Shortest._length: " << Shortest._length << endl;

    while(ResultLength < Shortest._length)
    {
        intBuf = *curCurShort + *curCurLong + transfer - 3 * Z;
        sprintf(chBuf, "%d", intBuf);
        //cout << chBuf <<  endl;
        if(strlen(chBuf) > 1)
        {
            *curCurRes = chBuf[1];
            transfer = chBuf[0];
        } else {
            *curCurRes = chBuf[0];
            transfer = Z;
        }
        curCurShort++, curCurLong++, curCurRes++; ResultLength++;
    }

    if (transfer != Z)
    {
        *curCurRes = transfer;
        ++ResultLength;
    }

    resultDigits[ResultLength] = '\0';
    //cout << "result digits: " << resultDigits;
    Result.Create(ResultLength, resultDigits);

    return Result; 
    
}
Dec Dec::Dcr(const Dec &Operand)
{

    Dec Left = *this, Right = Operand, Result;
    int intBuf = 0, ResultLength = 0;
    char chBuf[2], transfer = Z;
    char *resultDigits = new char[Left._length + 1];
    
    char *curCurLeft = Left._digits;
    char *curCurRight = Right._digits;
    char *curCurRes = resultDigits;

    if (Left._length < Right._length)
    {
        Result.Create(1, "0");
        return Result;
    }

    while(ResultLength < Left._length)
    {
        intBuf = (*curCurLeft - Z) - (*curCurRight - Z) - (transfer - Z);

        if (ResultLength + 1 > Left._length)
        {
            
        }
        cout << "intBuf: " << intBuf << endl;
        ResultLength++;
    }
   
    


    return Operand;
}

/*
        Dec Mul(const &Dec);
        Dec Div(const &Dec);
        bool GrThen(const &Dec);
        bool LsThen(const &Dec);
        bool Eq(Const &Dec);
*/

