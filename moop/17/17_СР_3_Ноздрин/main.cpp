#include <iostream>
#include <random>
#include <time.h>

#include "array.h"

using namespace std;

int main()
{

    srand(time(NULL));

    int *inArray1 = new int[ARR_SIZE];
    int *inArray2 = new int[ARR_SIZE];
    initArray(inArray1, ARR_SIZE, 10000, 20000);
    initArray(inArray2, ARR_SIZE, 10000, 20000);
    SortArray sArray1(inArray1, ARR_SIZE);
    SortArray *sArray2 = new SortArray(inArray2, ARR_SIZE);
    cout << "--------SortArray class testing---------" << endl;
    cout << "unsorted instance: " << sArray1 << endl;
    sArray1.foreach();
    cout << "sorted left operand: " << sArray1 << endl;
    cout << "right operand: " << *sArray2 << endl;
    sArray1.sum(*((Array *)(sArray2))); //ugly hack with C-style type cast. 
    cout << "summing up: " << sArray1 << endl;

    return 0;
}
