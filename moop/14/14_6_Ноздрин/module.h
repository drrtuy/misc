#ifndef HMODULE

#define HMODULE

#include "clock.h"


enum exCodes {  HOURNEGATIV, MINNEGATIV, HOUROVER, MINOVER };

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

Clock *getInput();
void testHoursMinsDomains();

#endif
