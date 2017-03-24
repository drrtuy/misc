#include <stdlib.h>
#include <string.h>

#include "module.h"

//
// Функция возвращает преобразованную строку в main.
//
//in1 string строка, введённая пользователем.
//
//out string преобразованная строка.
//
char *convert(char *input)
{
    static char result[BUF_LEN + 1];
    char *cursor = result;
    int depth = 1;

    strncpy(result, input, strlen(input));
   
    while (*cursor != '\0') {
        if (*cursor == '(') {
            *cursor = getOpenBrace(depth++);
        } else if (*cursor == ')') {
            *cursor = getCloseBrace(depth--);
        }
        cursor++;  
    } 

    return result;
}

//
// Функция возвращает открывающую скобку, соответствующую количествую уже открытых скобок.
//
//in1 int глубина - кол-во открытых скобок.
//
//out char символ открывающейся скобки.
//
char getOpenBrace(int depth)
{
    static char result;

    switch(depth) {
    case 1:
        result = '('; break;
    case 2: 
        result = '['; break;
    default: 
        result = '{';
    }

    return result;
}

//
// Функция возвращает закрывающую скобку, соответствующую количествую ещё открытых скобок.
//
//in1 int глубина - кол-во открытых скобок.
//
//out char символ закрывающей скобки.
//
char getCloseBrace(int depth)
{
    static char result;

    switch(depth) {
    case 1:
        result = ')'; break;
    case 2:
        result = ')'; break;
    case 3: 
        result = ']'; break;
    default: 
        result = '}';
    }

    return result;
}

