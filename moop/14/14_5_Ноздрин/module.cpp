#include <iostream>

#include "module.h"
#include "clock.h"

using namespace std;

//
// Создание объекта ручным вводом.
//
Clock *getInput()
{
    int min, hours;

    cout << "Enter the hours value: " << endl;
    cin >> hours;

    cout << "Enter the min value: " << endl;
    cin >> min;

    Clock *result = new Clock(min, hours);
    return result;
}

//
// Проверка срабатывания exception на разных наборах данных.
// in1 *Clock
//
void testHoursMinsDomains()
{
    int tstHoursArr[] = {0, -1, 1};
    int tstMinsArr[] = {0, -1, 1};
    Clock *cl;

    /*
    for(unsigned int it = 0; it < 3; it++)
    {
        for(unsigned int i = 0; i < 3; i++)
        {
            cl = new Clock(tstMinsArr[it], tstHoursArr[i]);
            if(cl->_failed)
                continue;
            cout << "Clock hours: " << cl->_hours << endl;
            cout << "Clock mins: " << cl->_minutes << endl;
        }
    }
    */

    Clock *cl1 = new Clock(34, 1);
    Clock *cl2 = new Clock(33, 24);

    cl1->getDiff((const Clock) *cl2);
    
}
