#include <iostream>
#include <string.h>

#include "module.h"
#include "dec.h"

using namespace std;

void checkAddition()
{
    Dec A, B, C;
    char left[] = "0";
    char right[] = "0";
    cout << "Summing " << left << " and " << right << " up." << endl;
    A.Create(strlen(left), left);
    B.Create(strlen(right), right);
    C = A.Add(B);
    cout << "add result " << C.outPut() << endl;

    char n_left[] = "11";
    char n_right[] = "11111";
    cout << "Summing " << n_left << " and " << n_right << " up." << endl;
    A.Create(strlen(n_left), n_left);
    B.Create(strlen(n_right), n_right);
    C = A.Add(B);
    cout << "add result " << C.outPut() << endl;

}   

void checkDecrement()
{
    Dec A, B, C;
    char left[] = "9";
    char right[] = "11";
    A.Create(strlen(left), left);
    B.Create(strlen(right), right);
    C = A.Dcr(B);
    cout << "Decrementing " << left << " by " << right << endl;
    cout << "decrement result " << C.outPut() << endl;

    char n_left[] = "11111";
    char n_right[] = "99";
    cout << "Decrementing " << n_left << " by " << n_right << endl;
    A.Create(strlen(n_left), n_left);
    B.Create(strlen(n_right), n_right);
    C = A.Dcr(B);
    cout << "decrement result " << C.outPut() << endl;

}   

void checkEquality()
{
    Dec A, B;
    char left[] = "111";
    char right[] = "222"; 
    
    A.Create(strlen(left), left);
    B.Create(strlen(right), right);
   
    cout << "Comparing two numbers" << endl; 
    cout << left << " == " << right << " is " << A.Eq(B) << endl;

    A.Create(strlen(left), left);
    B.Create(strlen(left), left);
   
    cout << "Comparing two numbers" << endl; 
    cout << left << " == " << left << " is " << A.Eq(B) << endl;

}
