#include <stdlib.h>
#include <stdio.h>

#include "module.h"

//
// Функция шифрует строку in1 и сохраняет её в in2.
//
//in1 wchar_t* куда сохраняем
//in2 wchar_t* что шифруем
//
//
void crypt(wchar_t *output, wchar_t const *input)
{
    wchar_t buf[BUF_LEN / 2 + 2];
    wchar_t const *curInput = input;
    wchar_t *curOutput = output;
    wchar_t *curBuf = buf;    
    int inpIndex = 0;

    while((*curInput != L'\n') && (*curInput != L'\n')) {
        if((inpIndex++ % 2) == 1) {
            *curOutput = *curInput;
            curOutput++; curInput++;
        } else {
            *curBuf = *curInput;
            curBuf++; curInput++;
        }
    }

    curBuf--;

    while(curBuf >= buf) {
        *curOutput = *curBuf;
        curOutput++; curBuf--;
    }
    
    *curOutput = L'\0';

}
