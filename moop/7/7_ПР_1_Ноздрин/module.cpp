#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "module.h"

//
// Функция подсчитывающая количество цифр в строке.
//
//in1 const char* строка, цифры которой подсчитывает функция.
//
//out int количество цифр, найденных в строке.
//
int countDigits(const char *str)
{
    int result = 0;
    char *cursor = NULL;

    cursor = (char *) str;

    while(*cursor != '\0') {
        if (isDigit(cursor++)) {
            result++;
        }
    }

    return result;
}

//
// Функция проверяет является ли аргумент цифрой.
//
//in1 char* символ для проверки.
//
//out bool
//
bool isDigit(char *chr)
{
    bool result = false;
    char digits[] = "0123456789";
    char *cursor = digits;
   
    while(*cursor) {
        if (*chr == *cursor) {
            result = true;
            break;
        }
        cursor++;
    }

    return result;
}
