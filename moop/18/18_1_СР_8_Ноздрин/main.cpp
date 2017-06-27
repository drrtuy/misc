#include <iostream>
#include <random>
#include <time.h>

#include "sort.h"
#include "rational.h"

using namespace std;

int main ()
{

    srand(time(NULL));

    int itArr[ARR_SIZE];
    long lgArr[ARR_SIZE];
    short shArr[ARR_SIZE];
    float flArr[ARR_SIZE];
    double dbArr[ARR_SIZE];
    Rational raArr[ARR_SIZE];

    cout << "Testing template funcs using int" << endl;
    InitArray(itArr, ARR_SIZE, -10000, 10000);
    outPut("Array before sort", itArr, ARR_SIZE);
    doBubbleSort(itArr, ARR_SIZE);
    outPut("Array after sort", itArr, ARR_SIZE);

    cout << "Testing template funcs using long" << endl;
    InitArray(lgArr, ARR_SIZE, -10000L, 10000L);
    outPut("Array before sort", lgArr, ARR_SIZE);
    doBubbleSort(lgArr, ARR_SIZE);
    outPut("Array after sort", lgArr, ARR_SIZE);

    cout << "Testing template funcs using short" << endl;
    InitArray(shArr, ARR_SIZE, static_cast<short>(128), static_cast<short>(512));
    outPut("Array before sort", shArr, ARR_SIZE);
    doBubbleSort(shArr, ARR_SIZE);
    outPut("Array after sort", shArr, ARR_SIZE);

    cout << "Testing template funcs using float" << endl;
    InitArray(flArr, ARR_SIZE, static_cast<float>(-1.05e4), static_cast<float>(1.05e4));
    outPut("Array before sort", flArr, ARR_SIZE);
    doBubbleSort(flArr, ARR_SIZE);
    outPut("Array after sort", flArr, ARR_SIZE);

    cout << "Testing template funcs using double" << endl;
    InitArray(dbArr, ARR_SIZE, -1.05e7, 1.05e7);
    outPut("Array before sort", dbArr, ARR_SIZE);
    doBubbleSort(dbArr, ARR_SIZE);
    outPut("Array after sort", dbArr, ARR_SIZE);

    cout << "Testing template funcs using custom Rational class" << endl;
    InitArray(raArr, ARR_SIZE, Rational(-100, -100), Rational(100, 100));
    outPut("Array before sort", raArr, ARR_SIZE);
    doBubbleSort(raArr, ARR_SIZE);
    outPut("Array after sort", raArr, ARR_SIZE);
 
    return 0;
}
