#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bitstring.h"
#include "module.h"

using namespace std;

//        char *_bits;
//        int maxLength;
//        int _length;

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

    sprintf(result, "%s %s", msg, _bits);
/*
    for (int i =0; i <= strlen(result); i++)
    {
        cout << result[i] << endl;
    }
    cout << "result str: " << result <<endl;
*/
    return result;
}

void BitString::stdoutPut(const char *msg)
{
    cout << msg << endl;
    cout << _bits << endl;
}

BitString BitString::And(const BitString &Operand)
{
    char extraBit = '0';
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

BitString BitString::Or(const BitString &bitString)
{
    BitString result;    
    return result;
}
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
    int i = Longest._length - 1;
    bool diffSize = Longest._length != Shortest._length;

    while(i >= 0)
    {
        //cout << "Cur value short " << *curPosShort << endl;
        //cout << "Cur value long " << *curPosLong << endl;
        if ((diffSize) && (Shortest._length < i) && (*curPosShort != *curPosLong ))
        {
            *curPosRes = '1';
        } else if ((diffSize) && (*curPosLong == '1'))
        {
            *curPosRes = '1';
        } else if((!diffSize) && (*curPosShort != *curPosLong ))
        {
            *curPosRes = '1';
        }
        curPosRes--; curPosLong--; curPosShort--; i--; 
    }
   
    result.init(Longest._length, _bits); 
   
    return result;
}
BitString BitString::Not()
{
    BitString result;
    char *_bits; //local _bits value

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
