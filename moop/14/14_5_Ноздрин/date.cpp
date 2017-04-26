#include <iostream>

#include "module.h"
#include "date.h"

using namespace std;

//
// Конструктор по умолчанию
//
Date::Date()
{
    _day = 0;
    _month = 0;
    _failed = false;
}

//
// Initializer
// in1 int день
// in2 int месяц
//
Date::Date(int day, int month)
{
    try
    {
        if(day < 0)
            throw TMyException(DAYNEG, day);
        if(month < 0)
            throw TMyException(MONTHNEG, month);
		if(month > 12)
            throw TMyException(MONTHOVER, month);
		if(day > DAYS[month])
            throw TMyException(DAYOVER, day);
        
        _day = day;
        _month = month;
        _failed = false;
    }
    catch (TMyException &except)
    { 
        if((except._exceptionCode == DAYNEG) || (except._exceptionCode == DAYOVER))
        {
            cout << "The day of the date is negative or bigger then number of days in the month: " << except._wrongValue << endl;
        }
        else
        {
            cout << "The mntho of the date is negative or bigger then 12: " << except._wrongValue << endl;
        }
        _failed = true;
    }

}

//
// Конструктор копирования
//
Date::Date(const Date &cl)
{
    _day = cl._day;
    _month = cl._month;
    _failed = cl._failed;
}

void Date::getDiff(const Date &endCl)
{
    Date *beginCl = this;
    signed int dayDiff = 0;
    signed int monthDiff = 0;
    dayDiff = endCl._day - beginCl->_day;
    monthDiff = endCl._month - beginCl->_month;
    try
    {
        if((monthDiff <0) || ((monthDiff == 0) && (dayDiff < 0)))
            throw TMyException(DAYNEG, dayDiff);
		for(int i = beginCl->_month; i < endCl._month; i++)
			dayDiff += DAYS[i];
        cout << "Period length in days: " << dayDiff << endl;
    }
    catch (TMyException &except)
    {
            cout << "Start date > end date." << endl;
    }

}
























