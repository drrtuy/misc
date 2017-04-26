#include <iostream>

#include "module.h"
#include "clock.h"

using namespace std;

/*
int _minutes;
int _hours;
*/

//
// Конструктор по умолчанию
//
Clock::Clock()
{
    _minutes = 0;
    _hours = 0;
    _failed = false;
}

//
// Initializer
// in1 int минуты
// in2 int часы
//
Clock::Clock(int minutes, int hours)
{
    try
    {
        if(minutes < 0)
            throw TMyException(MINNEGATIV, minutes);
        if(minutes > 60)
            throw TMyException(MINOVER, minutes);
        if(hours < 0)
            throw TMyException(HOURNEGATIV, hours);
        if(hours > 24)
            throw TMyException(HOUROVER, hours);
        
        _minutes = minutes;
        _hours = hours;
        _failed = false;
    }
    catch (TMyException &except)
    { 
        if((except._exceptionCode == MINNEGATIV) || (except._exceptionCode == MINOVER))
        {
            cout << "Negative min value was entered: " << except._wrongValue << endl;
        }
        else
        {
            cout << "Negative hours value was entered: " << except._wrongValue << endl;
        }
        _failed = true;
    }

}

//
// Конструктор копирования
//
Clock::Clock(const Clock &cl)
{
    _minutes = cl._minutes;
    _hours = cl._hours;
    _failed = cl._failed;
}

void Clock::getDiff(const Clock &endCl)
{
    Clock *beginCl = this;
    signed int minDiff = 0;
    signed int hoursDiff = 0;
    minDiff = endCl._minutes - beginCl->_minutes;
    hoursDiff = endCl._hours - beginCl->_hours;
    try
    {
        if((hoursDiff <0) || ((hoursDiff == 0) && (minDiff < 0)))
            throw TMyException(MINNEGATIV, minDiff);
        cout << "Call duration in mins: " << hoursDiff * 60 + minDiff << endl;
    }
    catch (TMyException &except)
    {
            cout << "The call finished before it had started." << endl;
    }

}
























