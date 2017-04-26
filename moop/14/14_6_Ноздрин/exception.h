#ifndef HMODULE

#define HMODULE

enum exCodes {  HOURNEGATIV, MINNEGATIV, HOUROVER, MINOVER };

struct TMyException
{
    exCodes _exeptionCode;
    int _minutes;
    int _hours;

    explicit TMyException(exCodes exeptionCode, int minutes, int hours)
    {
        _exeptionCode = exeptionCode;
        _minutes = minutes;
        _hours = hours;
    };
};

#endif
