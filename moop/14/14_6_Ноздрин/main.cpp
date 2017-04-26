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
        delete cl;
    }

    return 0;
}
