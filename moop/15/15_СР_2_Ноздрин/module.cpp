#include <iostream>

#include "bitstring.h"

using namespace std;

//
//Функция тестирует метод And класса BitString, выводя таблицу истинности
// и выполняя операцию над произвольными строками.
//
void checkConstrDestr()
{
    BitString A(3 , "010");
    cout << "<<<<Checking constructor>>>>" << endl;
    cout << A.outPut("Premade object A. A._bits: ") << endl;

    BitString B = A;

    cout << B.outPut("Premade object B. B._bits: ") << endl;
}

//
//Функция тестирует метод And класса BitString, выводя таблицу истинности
// и выполняя операцию над произвольными строками.
//
void checkAnd() 
{
    BitString A(1, "0");
    BitString B(1, "0");
    BitString *C;

    cout << "<<<Checking AND operation>>>" << endl;
    C = A & B;
    cout << A.outPut("Bit string value A ") << B.outPut(" Bit string value B ") << "\t" << C->outPut(" Anded bit string ") << endl;

    //printf("Check %p\n", &C);

    A.init(1, "1");
    B.init(1, "0");
    C = A & B;
    cout << A.outPut("Bit string value A ") << B.outPut(" Bit string value B ") << "\t" << C->outPut(" Anded bit string ") << endl;

    //printf("Check %p\n", &C);  

    A.init(1, "0");
    B.init(1, "1");
    C = A & B;
    cout << A.outPut("Bit string value A ") << B.outPut(" Bit string value B ") << "\t" << C->outPut(" Anded bit string ") << endl;


    //printf("Check %p\n", &C);   

    A.init(1, "1");
    B.init(1, "1");
    C = A & B;
    cout << A.outPut("Bit string value A ") << B.outPut(" Bit string value B ") << "\t" << C->outPut(" Anded bit string ") << endl;

    //printf("Check %p\n", &C);   

    A.init(5, "11111");
    B.init(4, "0001");
    C = A & B;
    cout << A.outPut("Bit string value A ") << B.outPut(" Bit string value B ") << "\t" << C->outPut(" Anded bit string ") << endl;

    //printf("Check %p\n", &C);   
}

//
//Функция тестирует метод OR класса BitString, выводя таблицу истинности
// и выполняя операцию над произвольными строками.
//
void checkOr()
{
    BitString *A = new BitString(1, "0");
    BitString *B = new BitString(1, "0");
    BitString *C;

    cout << "<<<Checking OR operation>>>" << endl;

    C = *A | *B;
    cout << A->outPut("Bit string value A ") << B->outPut(" Bit string value B ") << "\t" << C->outPut(" Ored bit string ") << endl;

    A->init(1, "1");
    B->init(1, "0");
    C = *A | *B;
    cout << A->outPut("Bit string value A ") << B->outPut(" Bit string value B ") << "\t" << C->outPut(" Ored bit string ") << endl;
    
    A->init(1, "0");
    B->init(1, "1");
    C = *A | *B;
    cout << A->outPut("Bit string value A ") << B->outPut(" Bit string value B ") << "\t" << C->outPut(" Ored bit string ") << endl;

    A->init(1, "1");
    B->init(1, "1");
    C = *A | *B;
    cout << A->outPut("Bit string value A ") << B->outPut(" Bit string value B ") << "\t" << C->outPut(" Ored bit string ") << endl;

    A->init(5, "11111");
    B->init(4, "0001");
    C = *A | *B;
    cout << A->outPut("Bit string value A ") << B->outPut(" Bit string value B ") << "\t" << C->outPut(" Ored bit string ") << endl;
}



//
//Функция тестирует метод XOR класса BitString, выводя таблицу истинности
// и выполняя операцию над произвольными строками.
//
void checkXor()
{
    BitString *A = new BitString(1, "0");
    BitString *B = new BitString(1, "0");
    BitString *C;

    cout << "<<<Checking XOR operation>>>" << endl;

    A->init(1, "0");
    B->init(1, "0");
    C = *A ^ *B;
    cout << A->outPut("Bit string value A ") << B->outPut(" Bit string value B ") << "\t" << C->outPut(" Xored bit string ") << endl;

    A->init(1, "1");
    B->init(1, "0");
    C = *A ^ *B;
    cout << A->outPut("Bit string value A ") << B->outPut(" Bit string value B ") << "\t" << C->outPut(" Xored bit string ") << endl;
    
    A->init(1, "0");
    B->init(1, "1");
    C = *A ^ *B;
    cout << A->outPut("Bit string value A ") << B->outPut(" Bit string value B ") << "\t" << C->outPut(" Xored bit string ") << endl;

    A->init(1, "1");
    B->init(1, "1");
    C = *A ^ *B;
    cout << A->outPut("Bit string value A ") << B->outPut(" Bit string value B ") << "\t" << C->outPut(" Xored bit string ") << endl;

    A->init(5, "11111");
    B->init(4, "0001");
    C = *A ^ *B;
    cout << A->outPut("Bit string value A ") << B->outPut(" Bit string value B ") << "\t" << C->outPut(" Xored bit string ") << endl;
}

//
//Функция тестирует метод NOT класса BitString, выводя таблицу истинности
// и выполняя операцию над произвольными строками.
//
void checkNot()
{

    BitString *A = new BitString(1,"1");
    BitString *B;

    cout << "<<<Checking NOT operation>>>" << endl;

    cout << A->outPut("Bit string init value: ");
    B = !*A;
    cout << B->outPut(" op result: ") << endl;

    A->init(1, "0");
    cout << A->outPut("Bit string init value: ");
    B = !*A;
    cout << B->outPut(" op result: ") << endl;
    
    A->init(5, "10101");
    cout << A->outPut("Bit string init value: ");
    B = !*A;
    cout << B->outPut(" op result: ") << endl;
}
