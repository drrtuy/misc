#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

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
        _overflow = false;
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
        char *argDigCursor = (char *) digits;
        char *intDigCursor = _digits;
        int i = 0;
        while(i++ < length)
        {
            *intDigCursor++ = *argDigCursor++;
        }
        //strncpy(_digits, digits, length);
        _digits[length] = '\0';
    } else {
        cout << "Too big Dec" << endl;
        abort();
    }

    _length = length;
    _overflow = false;
    
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
    char *_digitsCur = _digits;
    int i = 0;

    while(i++ < _length)
    {
        *resDigitsCur++ = *_digitsCur++;
    //    cout << "src digit: " << *_digitsCur << " dst digit: " << *resDigitsCur << endl;
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
    if (this->_length < Operand._length)
        return *this;
    return Operand;
}

//
// Функция возвращает строку наоборот.
// in1 char *
// out1 char *
//
char *Dec::_reverseStr(const char *input)
{
    int length = strlen(input);
    char *result = new char[length + 1];
    result[length] = '\0'; 
    char *resCursor = &result[length - 1];
    char *inpCursor = (char *) input;
    
    while(resCursor != result - 1)
    {
        //cout << "inp Cur value" << *inpCursor << endl;
        *resCursor-- = *inpCursor++;
    }

    return result;
}

//
// Функция сложения двух Dec. Поразрядно складываем цифры чисел и цифру переноса. 
// in1 const Dec& правый операнд сложения 
// out Dec результат сложения
//
Dec Dec::Add(const Dec &Operand)
{
    Dec Longest = *this, Shortest = Operand, result;
    int intBuf = 0, resultLength = 0;
    char chBuf[2], transfer = Z;
    char curShortDigit = '0';
    char *resultDigits = new char[Longest._length + 2];
    
    // Определяем число с бОльшим и меньшим количествами цифр.
    Longest = this->_getLongest(Operand);
    Shortest = this->_getShortest(Operand);


    char *curCurLong = Longest._digits;
    char *curCurShort = Shortest._digits;
    char *curCurRes = resultDigits;

    cout << " Shortest._length: " << Shortest._length << endl;

    // Идём по цифрам числа с большим количеством цифр.
    while(resultLength < Longest._length) 
    {
        // Если цифры "короткого" числа ещё не закончились, то берём цифру.
        if((resultLength + 1) <= Shortest._length)
        {
            curShortDigit = *curCurShort;
        } else 
        {
            curShortDigit = '0';
        }

        intBuf = curShortDigit + *curCurLong + transfer - 3 * Z;
        // Представляем сумму как число.
        sprintf(chBuf, "%d", intBuf);

        // Есть ли перенос. 
        if(strlen(chBuf) > 1)
        {
            // Очередная цифра суммы
            *curCurRes = chBuf[1];  
            // Перенос
            transfer = chBuf[0];
        } else {
            *curCurRes = chBuf[0];
            transfer = Z;
        }
        curCurShort++, curCurLong++, curCurRes++; resultLength++;
    }

    if (transfer != Z)
    {
        *curCurRes = transfer;
        ++resultLength;
    }

    resultDigits[resultLength] = '\0';
    cout << "result digits: " << resultDigits;
    result.Create(resultLength, _reverseStr(resultDigits));

    result._overflow = false;
    return result; 
    
}

//
// Функция вычитания двух Dec. Поразрядно вычитаем цифры чисел, учитывая перенос. 
// Возвращает Dec = 0, если уменьшаемое меньше вычитаемого.
// this Dec уменьшаемое
// in1 const Dec& вычитаемое 
// out Dec разность
//
Dec Dec::Dcr(const Dec &Operand)
{

    Dec Left = *this, Right = Operand, result;
    int intBuf = 0, resultLength = 0;
    char chBuf = '0', transfer = Z;
    char *resultDigits = new char[Left._length + 1];
    
    char *curCurLeft = Left._digits;
    char *curCurRight = Right._digits;
    char curOpDigit = *curCurRight;
    char *curCurRes = resultDigits;

    // Если длина строки цифр уменьшаемого < длины строки вычитаемого.
    if (Left._length < Right._length)
    {
        result.Create(1, "0");
        result._overflow = true;
        return result;
    }

    // Идём по строке цифр уменьшаемого.
    while((resultLength + transfer - Z) < Left._length)
    {
        // Берём очередную цифру из вычитаемого, если ещё есть.
        if((resultLength + 1) <= Right._length)
        {
            //cout << "get next digit" << endl;
            curOpDigit = *curCurRight;
        } else 
        {
            curOpDigit = '0';
        }

        // Вычисляем значение цифры разности с помощью ASCII кодов цифр.
        intBuf = (*curCurLeft - Z) - (curOpDigit - Z) - (transfer - Z);
        //cout << "intBuf: " << intBuf << endl;
        
        // Если в буфере отрицательное число, и в уменьшаемом не осталось цифр.
        if ((intBuf < 0) && (resultLength + 2 > Left._length))
        {
            result.Create(1, "0");
            result._overflow = true;
            return result;
        } else if (intBuf < 0) // Вычитаем и учитываем перенос на следующем шаге.
        {
            //cout << "set transfer base" << endl;
            intBuf = 10 + intBuf;
            transfer = '1';
        } else
        {
            //cout << "zero transfer base" << endl;
            transfer = '0';
        }

        sprintf(&chBuf, "%d", intBuf);
        *curCurRes = chBuf;

        //cout << "intBuf: " << intBuf << " resutLength: " << resultLength << endl;
        resultLength++; curCurLeft++; curCurRight++; curCurRes++;
    }

    if(transfer != Z) 
    {
        result.Create(1, "0");
        result._overflow = true;
        return result;
    }
  
    //cout << "resultDigits: " << resultDigits << " resutLength: " << resultLength << endl;
    result.Create(resultLength, _reverseStr(resultDigits)); 

    result._overflow = false;
    return result;
}

//
// Функция умножения двух Dec. Находим бОльшее число и складываем его n раз, 
// где n - значение меньшего числа.
// Возвращает Dec = 0, если уменьшаемое меньше вычитаемого.
// in1 const Dec& правый операнд 
// out Dec произведение
//
Dec Dec::Mul(const Dec &Operand)
{
    Dec Big = *this, Small = Operand, result;
    int digit = 0, i = 0;
    
    if(Big.LsThen(Small))
    {
        Big = Operand;
        Small = *this;
    }

    char *SmallCursor = Small._digits;

    result.Create(1, "0");

    // Проходим по цифрам меньшего числа.
    for(i = 0; i <= Small._length; i++)
    {
        digit = (Small._digits[i] - Z) * (int)pow(BASE, i);
        cout << "digit: " << digit << endl;
        // Складываем 
        while(digit-- > 0)
        {
            result = result.Add(Big);
            cout << "int result: " << result.outPut() << endl;
        } 
        cout << "result: " << result.outPut() << endl;
    }
 
    return result;
}
//
// Функция сравнения двух чисел на равенство между собой: 
// this == Operand
// in1 правый операнд
// out результат сравнения
// 
bool Dec::Eq(const Dec &Operand)
{
    return (_length == Operand._length)\
 && (!strncmp(_digits, Operand._digits, _length));    
}

//
// Операция сравнения двух чисел между собой:
// this > Operand
// in1 правый операнд
// out результат сравнения
// 
bool Dec::GrThen(const Dec &Operand)
{
    Dec diff = this->Dcr(Operand);
    return (*diff._digits != '0');
}

//
// Отношение сравнения двух чисел между собой:
// this < Operand
// in1 правый операнд
// out результат сравнения
// 
bool Dec::LsThen(const Dec &Operand)
{
    Dec diff = this->Dcr(Operand);
    return ((*diff._digits == '0') and (diff._overflow));
}


/*
        Dec Div(const &Dec);
*/
