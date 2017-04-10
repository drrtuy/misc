#include <iostream>

#include "bitstring.h"

using namespace std;

//
//Функция тестирует метод And класса BitString, выводя таблицу истинности
// и выполняя операцию над произвольными строками.
//
void checkAnd() 
{
    BitString *bsRefA = new BitString;
    BitString *bsRefB = new BitString;
    BitString C;

    cout << "<<<Checking AND operation>>>" << endl;

    bsRefA->init(1, "0");
    bsRefB->init(1, "0");
    C = bsRefA->And(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Anded bit string ") << endl;

    bsRefA->init(1, "1");
    bsRefB->init(1, "0");
    C = bsRefA->And(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Anded bit string ") << endl;
    
    bsRefA->init(1, "0");
    bsRefB->init(1, "1");
    C = bsRefA->And(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Anded bit string ") << endl;

    bsRefA->init(1, "1");
    bsRefB->init(1, "1");
    C = bsRefA->And(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Anded bit string ") << endl;

    bsRefA->init(5, "11111");
    bsRefB->init(4, "0001");
    C = bsRefA->And(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Anded bit string ") << endl;
}

//
//Функция тестирует метод OR класса BitString, выводя таблицу истинности
// и выполняя операцию над произвольными строками.
//
void checkOr()
{
    BitString *bsRefA = new BitString;
    BitString *bsRefB = new BitString;
    BitString C;

    cout << "<<<Checking OR operation>>>" << endl;

    bsRefA->init(1, "0");
    bsRefB->init(1, "0");
    C = bsRefA->Or(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Ored bit string ") << endl;

    bsRefA->init(1, "1");
    bsRefB->init(1, "0");
    C = bsRefA->Or(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Ored bit string ") << endl;
    
    bsRefA->init(1, "0");
    bsRefB->init(1, "1");
    C = bsRefA->Or(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Ored bit string ") << endl;

    bsRefA->init(1, "1");
    bsRefB->init(1, "1");
    C = bsRefA->Or(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Ored bit string ") << endl;

    bsRefA->init(5, "11111");
    bsRefB->init(4, "0001");
    C = bsRefA->Or(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Ored bit string ") << endl;
}



//
//Функция тестирует метод XOR класса BitString, выводя таблицу истинности
// и выполняя операцию над произвольными строками.
//
void checkXor()
{
    BitString *bsRefA = new BitString;
    BitString *bsRefB = new BitString;
    BitString C;

    cout << "<<<Checking XOR operation>>>" << endl;

    bsRefA->init(1, "0");
    bsRefB->init(1, "0");
    C = bsRefA->Xor(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Xored bit string ") << endl;

    bsRefA->init(1, "1");
    bsRefB->init(1, "0");
    C = bsRefA->Xor(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Xored bit string ") << endl;
    
    bsRefA->init(1, "0");
    bsRefB->init(1, "1");
    C = bsRefA->Xor(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Xored bit string ") << endl;

    bsRefA->init(1, "1");
    bsRefB->init(1, "1");
    C = bsRefA->Xor(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Xored bit string ") << endl;

    bsRefA->init(5, "11111");
    bsRefB->init(4, "0001");
    C = bsRefA->Xor(*bsRefB);
    cout << bsRefA->outPut("Bit string value A ") << bsRefB->outPut(" Bit string value B ") << "\t" << C.outPut(" Xored bit string ") << endl;
}

//
//Функция тестирует метод NOT класса BitString, выводя таблицу истинности
// и выполняя операцию над произвольными строками.
//
void checkNot()
{

    BitString *bsRefA = new BitString;
    BitString B;

    cout << "<<<Checking NOT operation>>>" << endl;

    bsRefA->init(1, "1");
    cout << bsRefA->outPut("Bit string init value: ");
    B = bsRefA->Not();
    cout << B.outPut(" op result: ") << endl;

    bsRefA->init(1, "0");
    cout << bsRefA->outPut("Bit string init value: ");
    B = bsRefA->Not();
    cout << B.outPut(" op result: ") << endl;
    
    bsRefA->init(5, "10101");
    cout << bsRefA->outPut("Bit string init value: ");
    B = bsRefA->Not();
    cout << B.outPut(" op result: ") << endl;
}
