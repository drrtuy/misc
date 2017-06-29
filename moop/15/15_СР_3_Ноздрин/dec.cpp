#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef linux
#include <unistd.h>
#endif
#include <math.h>

#include "dec.h"

using namespace std;

//
// Def конструктор
// 
Dec::Dec()
{
    _digits = NULL;
    _length = 0;
    _overflow = false;
}

//
// Конструктор инициализации
// in1 int длина строки цифр
// in2 строка цифр
//
Dec::Dec(int length, const char *digits)
{
    if (length < MAX_LENGTH)
    {
        char *reverse = this->_reverseStr(digits);
        _digits = new char[length + 1];
        strncpy(_digits, reverse, length);
        _digits[length] = '\0';
    } else {
        cout << "Too big Dec" << endl;
        abort();
    }

    _length = length;
    _overflow = false;
}

//
// Конструктор инициализации
// in1 int число
//
Dec::Dec(int number)
{
    char *tmp = new char[MAX_LENGTH];
    char *revTmp;
    sprintf(tmp, "%d", number); 
    revTmp = this->_reverseStr(tmp);
    _length = strlen(revTmp);
    _digits = new char[_length + 1];
    strncpy(_digits, revTmp, _length);
    _overflow = false;
    delete tmp;
    delete revTmp;
}

//
// Конструктор копирования
// in1 &Dec
//
Dec::Dec(const Dec &Operand)
{
    _length = Operand._length;
    _digits = new char[_length + 1];
    strncpy(_digits, Operand._digits, _length);
    _digits[_length] = '\0'; 
    _overflow = Operand._overflow;
}

//
// Деструктор. Просто деструктор
//
Dec::~Dec()
{
    if (_digits != NULL)
        delete _digits;
    _digits = NULL;
    _length = 0;
    _overflow = false;
}

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
        char *reverse = this->_reverseStr(digits);
        _digits = new char[length + 1];
        strncpy(_digits, reverse, length);
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

bool Dec::getOverflow()
{
    return _overflow;
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
    char *_digitsCur = &_digits[_length-1];
    int i = 0;

    while(i++ < _length)
    {
        *resDigitsCur++ = *_digitsCur--;
    //    cout << "src digit: " << *_digitsCur << " dst digit: " << *resDigitsCur << endl;
    }

    return result;
}

//
// Ф-ия возвращает строку из цифр числа в превычной форме(слева старший разряд).
// out char* строка
//
std::ostream &operator<<(ostream& stream, const Dec &Operand)
{
    char *result = new char[Operand._length + 1];
    result[Operand._length] = '\0';
    char *resDigitsCur = result;
    char *_digitsCur = &Operand._digits[Operand._length-1];
    int i = 0;

    while(i++ < Operand._length)
    {
        *resDigitsCur++ = *_digitsCur--;
    }

    stream << result;
    return stream;
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

Dec *Dec::__getLongest( const Dec &Operand)                                                                                                                                                     
{
    if (this->_length > Operand._length)
        return this;
    return (Dec *) &Operand;
}

Dec *Dec::__getShortest( const Dec &Operand)                                                    {
    if (this->_length < Operand._length)
        return this;
    return (Dec *) &Operand;
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

Dec &Dec::operator=(const Dec &Operand)
{
    if(this != &Operand){
        if(_length != 0)
            delete[] _digits;
        _length = Operand._length;
        char *tmp = new char[_length+1];
        strncpy(tmp, Operand._digits, _length);
        tmp[_length] = '\0';
        _digits = tmp;
        _overflow = Operand._overflow;
    }
    return *this;
}

//
// Функция сложения двух Dec. Поразрядно складываем цифры чисел и цифру переноса. 
// in1 const Dec& правый операнд сложения 
// out Dec результат сложения
//
Dec &Dec::operator+(const Dec &Operand)
{
    Dec *Longest = this, *Shortest = (Dec *) &Operand;
    int intBuf = 0, resultLength = 0;
    char chBuf[2], transfer = Z;
    char curShortDigit = '0';
    char *resultDigits = new char[Longest->_length + 2];
    
    // Определяем число с бОльшим и меньшим количествами цифр.
    Longest = this->__getLongest(Operand);
    Shortest = this->__getShortest(Operand);


    char *curCurLong = Longest->_digits;
    char *curCurShort = Shortest->_digits;
    char *curCurRes = resultDigits;

    //cout << " Longest->_digits: " << Shortest->_digits << endl;
    //cout << " Shortest->_digits: " << Longest->_digits << endl;

    // Идём по цифрам числа с большим количеством цифр.
    while(resultLength < Longest->_length)
    {
        // Если цифры "короткого" числа ещё не закончились, то берём цифру.
        if((resultLength + 1) <= Shortest->_length)
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
    //cout << "result digits: " << resultDigits << endl;

    Dec *result = new Dec(resultLength, this->_reverseStr(resultDigits));
    //Dec *result = new Dec();
    result->_overflow = false;

    delete resultDigits;

    return *result;
}

//
// Функция вычитания двух Dec. Поразрядно вычитаем цифры чисел, учитывая перенос. 
// Возвращает Dec = 0, если уменьшаемое меньше вычитаемого.
// this Dec уменьшаемое
// in1 const Dec& вычитаемое 
// out Dec разность
//
Dec &Dec::operator-(const Dec &Operand)
{

    Dec *Left = this, *Right = (Dec *) &Operand;
    int intBuf = 0, resultLength = 0;
    char chBuf = '0', transfer = Z;
    char *resultDigits = new char[Left->_length + 1];
    
    char *curCurLeft = Left->_digits;
    char *curCurRight = Right->_digits;
    char curOpDigit = *curCurRight;
    char *curCurRes = resultDigits;

    // Если длина строки цифр уменьшаемого < длины строки вычитаемого.
    if (Left->_length < Right->_length)
    {
        Dec *result = new Dec(0);
        result->_overflow = true;
        return *result;
    }

    // Идём по строке цифр уменьшаемого.
    while((resultLength + transfer - Z) < Left->_length)
    {
        // Берём очередную цифру из вычитаемого, если ещё есть.
        if((resultLength + 1) <= Right->_length)
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
        if ((intBuf < 0) && (resultLength + 2 > Left->_length))
        {
            Dec *result = new Dec(0);
            result->_overflow = true;
            return *result;
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
        Dec *result = new Dec(0);
        result->_overflow = true;
        return *result;
    }
  
    //cout << "resultDigits: " << resultDigits << " resutLength: " << resultLength << endl;
    Dec *result = new Dec(resultLength, this->_reverseStr(resultDigits));
    result->_overflow = false;

    delete resultDigits;

    return *result;
}

//
// Функция умножения двух Dec. Находим бОльшее число и умножаем его. 
// in1 const Dec& правый операнд 
// out Dec произведение
//
Dec &Dec::operator*(const Dec &Operand)
{
    Dec *Big = this, *Small = (Dec *) &Operand;
    int buf;
    char *strBuf = new char[MAX_LENGTH];
    int digit = 0, i = 0;
    
    if(*Big < *Small)
    {
        Big = (Dec *) &Operand;
        Small = this;
    }

    // Проходим по цифрам меньшего числа.
    for(i = 0; i < Small->_length; i++)
    {
        digit += (Small->_digits[i] - Z) * (int)pow(BASE, i);
        //cout << "digit: " << digit << endl;
        //result = result.Add(Big);
    }
    sscanf(Big->outPut(), "%d", &buf);
    //cout << "Dec::Mul() buf: " << buf << endl;
    //cout << "Big: " << result.outPut() << endl;
    memset(strBuf, '\0', MAX_LENGTH);
    buf = buf * digit;
    sprintf(strBuf, "%d", buf);  

    //cout << "Dec::Mul() strBuf: " << strBuf << endl;

    Dec *result = new Dec(strlen(strBuf), strBuf);     

    delete strBuf; 

    return *result;
}

//
// Функция деления двух Dec. Если происходит деление на ноль, то обрываем программу.
// in1 const Dec& правый операнд 
// out Dec неполное частное
//
Dec &Dec::operator/(const Dec &Operand)
{
    Dec *Left = this, *Right = (Dec *) &Operand;
    int lBuf, rBuf;
    char *strBuf = new char[MAX_LENGTH];

    if(*Left < *Right)
    {
        Dec *result = new Dec(0);
        return *result;
    }/* else if (*Right->_digits == '0')
    {
        cout << "Dec::Div() Div by 0" << endl;
        abort();
    }
    */
    sscanf(Left->outPut(), "%d", &lBuf);
    sscanf(Right->outPut(), "%d", &rBuf);
    //cout << "Big: " << Big.outPut() << endl;
    memset(strBuf, '\0', MAX_LENGTH);
    lBuf = lBuf / rBuf;
    sprintf(strBuf, "%d", lBuf);  

    Dec *result = new Dec(strlen(strBuf), strBuf);     
    delete strBuf; 
 
    return *result;
}

//
// Функция сравнения двух чисел на равенство между собой: 
// this == Operand
// in1 правый операнд
// out результат сравнения
// 
bool Dec::operator==(const Dec &Operand)
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
bool Dec::operator>(const Dec &Operand)
{
    Dec *diff = new Dec();
    *diff = *this - Operand;
    return (*diff->_digits != '0');
}

//
// Отношение сравнения двух чисел между собой:
// this < Operand
// in1 правый операнд
// out результат сравнения
// 
bool Dec::operator<(const Dec &Operand)
{
    Dec *diff = new Dec();
    *diff = *this - Operand;
    return ((*diff->_digits == '0') && (diff->_overflow));
}
