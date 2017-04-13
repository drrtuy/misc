#include <iostream>

#include "module.h"
#include "dec.h"

using namespace std;

void checkAddition()
{
    Dec A, B, C;
    char left[] = "99";
    char right[] = "999";
/*
    A.Create(5, "12345");
    B.Create(6, "123456");
    cout << "digits are " << A.outPut() << endl;
    C = A._getLongest(B);
    cout << "longest " << C.outPut() << endl;
*/
    cout << "Summing " << left << " and " << right << " up." << endl;
    A.Create(2, "99");
    B.Create(3, "999");
    C = A.Add(B);
    cout << "add result " << C.outPut() << endl;

}   

void checkDecrement()
{
    Dec A, B, C;
/*
    A.Create(5, "12345");
    B.Create(6, "123456");
    cout << "digits are " << A.outPut() << endl;
    C = A._getLongest(B);
    cout << "longest " << C.outPut() << endl;
*/
    A.Create(2, "11");
    B.Create(1, "1");
    C = A.Dcr(B);
//    cout << "add result " << C.outPut() << endl;

}   


