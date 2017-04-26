#include <iostream>

#include "module.h"
#include "date.h"

using namespace std;

int main()
{
    cout << "Date input checker." << endl;

    testDateDomain();

    while(true)
    {
		cout << "Enter two dates to calculate the period length." << endl;
		cout << "Period starts at: " << endl;
        Date *date1 = getInput();
		cout << "Period finishes at: " << endl;
		Date *date2 = getInput();
        if((date1->_failed) || (date2->_failed))
        {
			delete date1; delete date2;
            continue;
        }
		date1->getDiff(*date2);
        delete date1; delete date2;
    }

    return 0;
}
