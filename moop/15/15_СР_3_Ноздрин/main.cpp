#include <iostream>
#include <string.h>

#include "module.h"
#include "dec.h"

using namespace std;

int main ()
{

    cout << " Dec class operations. " << endl;

    checkAddition();
    checkDecrement();
    checkEquality();
    checkGrThen();
    checkLessThen();
    checkMul();
    checkDiv();

    return 0;
}
