#ifndef HMODULE

#define HMODULE

#include "date.h"


enum exCodes {  DAYNEG, MONTHNEG, DAYOVER, MONTHOVER };

struct TMyException
{
    exCodes _exceptionCode;
    int _wrongValue;

    explicit TMyException(exCodes exceptionCode, int value)
    {
        _exceptionCode = exceptionCode;
        _wrongValue = value;
    };
};

Date *getInput();
void testDateDomain();

#endif
