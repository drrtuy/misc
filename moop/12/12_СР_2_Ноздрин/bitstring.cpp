#include <iostream>
#include <string.h>
#include <stdio.h>

#include "bitstring.h"
#include "module.h"

using namespace std;

void BitString::init(int _length, const char *bitString)
{
    this->_length = _length;
    
    _bits = (char *) malloc(_length + 1);
    
    if(!_bits)
        cout << "Cannot allocate memory at BitString::init()" << endl;

    strncpy(_bits, bitString, (size_t) _length);
    _bits[_length] = '\0';
}

void BitString::create(int _length)
{
    this->_length = _length;
    _bits = new char[_length];
    _bits[_length] = '\0';
}

//
// Метод возвращает внутреннее представление битовой строки в форме строки.
// in1 char * сообщение, предществующее выводу битовой строки.
// out char * битовая строка
//
char *BitString::outPut(const char *msg)
{
    char *result;
    int totalLength = _length + strlen(msg) + 1;
    result = (char *) malloc(totalLength);
    
    if(!result)
        cout << "Cannot allocate memory at BitString::outPut()" << endl;

    snprintf(result, totalLength, "%s%s", msg, _bits);
/*
    for (int i =0; i <= strlen(result); i++)
    {
        cout << result[i] << endl;
    }
    cout << "result str: " << result <<endl;
*/
    return result;
}

//
// Метод возвращает внутреннее представление битовой строки в форме строки в stdout.
// in1 char * сообщение, предществующее выводу битовой строки.
// out char * битовая строка
//
void BitString::stdoutPut(const char *msg)
{
    cout << msg << endl;
    cout << _bits << endl;
}

BitString BitString::And(const BitString &Operand)
{
    BitString Shortest = *this;
    BitString Longest = Operand;

    if (Shortest._length > Operand._length)
    {
        Shortest = Operand;
        Longest = *this;
    }

    /* Выделяем память под строку для хранения "битов" меньшего из операндов. Затем заполняем её нулями.*/
    char *_bits;
    
    _bits = (char *)malloc(sizeof(char) * Shortest._length);
    
    if(_bits == NULL) {
        cout << "Cannot allocate mem at BitString::And" << endl;
        abort();
    }

    memset(_bits, '0', Shortest._length);
    _bits[Shortest._length] = '\0';
         
    char *curPosShort = &Shortest._bits[Shortest._length - 1];
    char *curPosLong = &Longest._bits[Shortest._length - 1];
    char *curPosRes = &_bits[Shortest._length - 1];
    int i = Shortest._length;

    while( i-- > 0 )
    {
        //cout << "Cur value short " << *curPosShort << endl;
        //cout << "Cur value long " << *curPosLong << endl;
        if ((*curPosShort-- == '1') && (*curPosLong-- == '1'))
            *curPosRes = '1'; 
        curPosRes--;
    }
   
    BitString result;
    result.init(Shortest._length, _bits); 

    return result;
}

//
// Метод выполняет операцию OR над операндами экземплярами класса.
// in1 const BitString & второй операнд.
// out BitString
//
BitString BitString::Or(const BitString &Operand)
{
    BitString result;    
    char extraBit = '0';
    int curBitSum = 0;
    BitString Shortest = *this;
    BitString Longest = Operand;

    if (Shortest._length > Operand._length)
    {
        Shortest = Operand;
        Longest = *this;
    }

    int _length = Longest._length;

    /* Выделяем память под строку для хранения "битов" бОльшего из операндов. Затем заполняем её нулями.*/
    char *_bits;
    
    _bits = (char *)malloc(sizeof(char) * Longest._length + 1);
    
    if(_bits == NULL) {
        cout << "Cannot allocate mem at BitString::Or" << endl;
        abort();
    }

    memset(_bits, '1', Longest._length);
    _bits[Longest._length] = '\0';
         
    char *curPosShort = &Shortest._bits[Shortest._length - 1];
    char *curPosLong = &Longest._bits[Longest._length - 1];
    char *curPosRes = &_bits[Longest._length - 1];
    int i = Longest._length;

    while( i-- > Longest._length - Shortest._length )
    {
        //сумма значений символов, хранящихся в разрядах операндов и бите переноса.
        curBitSum = *curPosShort-- + *curPosLong-- + extraBit;
        //Если одна единица или три единицы в разрядах операндов или бита переноса
        if ((curBitSum == '1') || (curBitSum == 3 * '1'))
            *curPosRes = '1';
        // Если две, то бит переноса содержит единицу 
        if (curBitSum == '1' * 2 + '0')
        {
            *curPosRes = '0';
            extraBit = '1'; 
        } else {
            extraBit = '0';
        }
        curPosRes--;
    }

    //Прошли по битам пары операндов, идём по битам более длинного.
    while(curPosLong != Longest._bits - 1)
    {
        curBitSum = *curPosLong-- + extraBit;
        if (curBitSum == '1' * 2)
        {
            *curPosRes = '0';
            extraBit = '1'; 
        } else if (curBitSum == '1') {
            *curPosRes = '0';
            extraBit = '0';
        } else {
            extraBit = '0';
        }
    }

    // Если остался бит переноса, то увеличиваем длину битовой строки,
    // добавляя '1'.
    if (extraBit == '1')
    {
        char *_temp = _bits; 
        _bits = (char *)malloc(sizeof(char) * Longest._length + 2);
        
        if(_bits == NULL) {
            cout << "Cannot allocate mem at BitString::Or" << endl;
            abort();
        }

        strncpy(_bits + 1, _temp, Longest._length);
        _bits[0] = '1';
        _bits[Longest._length + 1] = '\0';
        free(_temp);
        _length++;
    }

    result.init(_length, _bits); 

    return result;
}

//
// Метод выполняет операцию OR над операндами экземплярами класса.
// in1 const BitString & второй операнд.
// out BitString
//
BitString BitString::Xor(const BitString &Operand)
{
    BitString result;
    BitString Shortest = *this;
    BitString Longest = Operand;

    if (Shortest._length > Operand._length)
    {
        Shortest = Operand;
        Longest = *this;
    }

    char *_bits;
    
    _bits = (char *)malloc(sizeof(char) * Longest._length + 1);

    if(_bits == NULL) {
        cout << "Cannot allocate mem at BitString::Xor" << endl;
        abort();
    }

    _bits[Longest._length] = '\0';

    memset(_bits, '0', Longest._length);
    _bits[Longest._length] = '\0';
         
    char *curPosShort = &Shortest._bits[Shortest._length - 1];
    char *curPosLong = &Longest._bits[Longest._length - 1];
    char *curPosRes = &_bits[Longest._length - 1];
    int i = Longest._length;
    int lengthDiff = Longest._length - Shortest._length;
    bool diffSize = Longest._length != Shortest._length;

    while(i >= 0)
    {
        // Операнды разной длины и мы движемся по обоим.
        if ((diffSize) && (i > lengthDiff ))
        {
            if (*curPosShort != *curPosLong)
                *curPosRes = '1';
            if (*curPosShort == *curPosLong)
                *curPosRes = '0';
        // Операнды разной длины и мы движемся только по одному,
        // т.к. биты второго уже пройдены.
        } else if ((diffSize) && (*curPosLong == '1')) 
        {
            cout << "2st" << endl;
            *curPosRes = '1';
        // Операнды одинаковой длины и мы сравниваем биты разрядов.
        } else if((!diffSize) && (*curPosShort != *curPosLong ))
        {
            cout << "3d" << endl;
            *curPosRes = '1';
        }
        curPosRes--; curPosLong--; curPosShort--; i--; 
    }
   
    result.init(Longest._length, _bits); 
   
    return result;
}
//
// Метод выполняет операцию NOT над битовой строкой объекта.
// out BitString
//
BitString BitString::Not()
{
    BitString result;
    char *_bits; 
    _bits = (char *)malloc(sizeof(char) * this->_length + 1);
    
    if(_bits == NULL) 
    {
        cout << "Cannot allocate mem at BitString::Not" << endl;
        abort();
    }
   
    strncpy(_bits, this->_bits, this->_length);
    _bits[this->_length] = '\0';
    char *resultCursor = _bits; 

    while (*resultCursor != '\0')
    {
        if(*resultCursor == '0')
        {
            *resultCursor++ = '1'; 
        } else {
            *resultCursor++ = '0';
        }
    }

    result.init(this->_length, _bits);

    return result;
}
