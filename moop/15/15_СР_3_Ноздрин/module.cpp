#include <iostream>
#include <string.h>

#include "module.h"
#include "dec.h"

using namespace std;

void checkAddition()
{
    cout << "############# + ############" << endl;
    Dec *A = new Dec(1);
    Dec *B = new Dec(100);
    Dec *C = new Dec();
    char left[] = "1";
    char right[] = "100";
    cout << "Summing " << left << " and " << right << " up." << endl;
    *C = *A + *B;
    cout << "add result " << *C << endl;

    char n_left[] = "11";
    char n_right[] = "11111";
    cout << "Summing " << n_left << " and " << n_right << " up." << endl;
    A->Create(strlen(n_left), n_left);
    B->Create(strlen(n_right), n_right);
    *C = *A + *B;
    cout << "add result " << *C << endl;
}   

void checkDecrement()
{
    cout << "############# - ############" << endl;
    Dec *A = new Dec(111);
    Dec *B = new Dec(222);
    Dec *C = new Dec();
    char left[] = "111";
    char right[] = "222";
    *C = *A - *B;
    cout << "Decrementing " << left << " by " << right << endl;
    cout << "decrement result " << *C << endl;

    char n_left[] = "11111";
    char n_right[] = "99";
    cout << "Decrementing " << n_left << " by " << n_right << endl;
    A->Create(strlen(n_left), n_left);
    B->Create(strlen(n_right), n_right);
    *C = *A - *B;
    cout << "decrement result " << *C << endl;

}   

void checkMul()
{
    cout << "############# * ############" << endl;
    Dec *A = new Dec(11);
    Dec *B = new Dec(100);
    Dec *C = new Dec();
    char left[] = "11";
    char right[] = "100";
    *C = *A * *B;
    cout << "Multiplying " << left << " by " << right << endl;
    cout << "Mul result " << *C << endl;

    char n_left[] = "11111";
    char n_right[] = "0";
    cout << "Multiplying " << n_left << " by " << n_right << endl;
    A->Create(strlen(n_left), n_left);
    B->Create(strlen(n_right), n_right);
    *C = *A * *B;
    cout << "Mul result " << *C << endl;
}   

void checkDiv()
{
    cout << "############# / ############" << endl;
    Dec *A = new Dec(11);
    Dec *B = new Dec(100);
    Dec *C = new Dec();
    char left[] = "11";
    char right[] = "100";
    *C = *A / *B;
    cout << "Divising " << left << " by " << right << endl;
    cout << "Div result " << *C << endl;

    char n_left[] = "11111";
    char n_right[] = "25";
    cout << "Divising " << n_left << " by " << n_right << endl;
    A->Create(strlen(n_left), n_left);
    B->Create(strlen(n_right), n_right);
    *C = *A / *B;
    cout << "Div result " << *C << endl;
}   

void checkEquality()
{
    cout << "############# == ############" << endl;
    Dec *A = new Dec(111);
    Dec *B = new Dec(222);
    char left[] = "111";
    char right[] = "222"; 
    
    cout << "Comparing two numbers" << endl; 
    cout << left << " == " << right << " is " << (*A == *B) << endl;

    A->Create(strlen(left), left);
    B->Create(strlen(left), left);
   
    cout << "Comparing two numbers" << endl; 
    cout << left << " == " << left << " is " << ( *A == *B ) << endl;
}

void checkGrThen()
{
    cout << "############# > ############" << endl;
    Dec *A = new Dec(111);
    Dec *B = new Dec(222);
    char left[] = "111";
    char right[] = "222";
    
    cout << "Comparing two numbers" << endl;
    cout << left << " > " << right << " is " << (*A > *B) << endl;

    char n_left[] = "222";
    char n_right[] = "111";

    A->Create(strlen(n_left), n_left);
    B->Create(strlen(n_right), n_right);
   
    cout << "Comparing two numbers" << endl;
    cout << n_left << " > " << n_right << " is " << (*A > *B) << endl;

}
void checkLessThen()
{
    cout << "############# < ############" << endl;
    Dec *A = new Dec(111);
    Dec *B = new Dec(222);
    char left[] = "111";
    char right[] = "222";
    
    cout << "Comparing two numbers" << endl;
    cout << left << " < " << right << " is " << (*A < *B) << endl;

    char n_left[] = "222";
    char n_right[] = "111";

    A->Create(strlen(n_left), n_left);
    B->Create(strlen(n_right), n_right);
   
    cout << "Comparing two numbers" << endl;
    cout << n_left << " < " << n_right << " is " << (*A < *B) << endl;
}

