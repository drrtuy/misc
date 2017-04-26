#include <iostream>

#include "module.h"
#include "date.h"

using namespace std;

//
// Создание объекта ручным вводом.
//
Date *getInput()
{
    int day, month;

    cout << "Day number is: " << endl;
    cin >> day;

    cout << "Month number is: " << endl;
    cin >> month;

    Date *result = new Date(day, month);
    return result;
}

//
// Проверка срабатывания exception на разных наборах данных.
// in1 *Date
//
void testDateDomain()
{
    Date *date1 = new Date(23, 2);
    Date *date2 = new Date(8, 3);
	
	cout << "Date format is month-day." << endl;
	cout << "The period starts at: " << date1->_month << "-" << date1->_day << endl;
	cout << "The period finishes at: " << date2->_month << "-" << date2->_day << endl;
    date1->getDiff((const Date) *date2);
	
	delete date1; delete date2;
	
	date1 = new Date(20, 2);
    date2 = new Date(1, 1);
	
	cout << "The period starts at: " << date1->_month << "-" << date1->_day << endl;
	cout << "The period finishes at: " << date2->_month << "-" << date2->_day << endl;
    date1->getDiff((const Date) *date2);
	
	delete date1; delete date2;
}