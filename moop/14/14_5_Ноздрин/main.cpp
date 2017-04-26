#include <iostream>

#include "module.h"
#include "clock.h"

using namespace std;

int main()
{
    cout << "Clock input checker." << endl;

    testHoursMinsDomains();

    while(true)
    {
        Clock *cl = getInput();
        if(cl->_failed)
        {
            continue;
        }
        delete cl;
    }

    return 0;
}
