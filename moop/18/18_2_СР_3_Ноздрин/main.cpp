#include <iostream>
#include <random>
#include <time.h>

#include "sort.h"
#include "vector.h"
#include "rational.h"

using namespace std;

int main ()
{

    srand(time(NULL));

    int itArr[ARR_SIZE];
    int singleIt;
    long lgArr[ARR_SIZE];
    long lgSingle;
    short shArr[ARR_SIZE];
    short shSingle;
    float flArr[ARR_SIZE];
    float flSingle;
    double dbArr[ARR_SIZE];
    double dbSingle;
    Rational raArr[ARR_SIZE];
    Rational raSingle;

    cout << "Testing template class using int" << endl;
    InitArray(itArr, ARR_SIZE, -10000, 10000);
    Vector<int> itVector(itArr, ARR_SIZE);
    itVector.outPut("itArr before delHead() call");
    singleIt = itVector.delHead();
    itVector.outPut("itArr after delHead() call");
    itVector.addTail(&singleIt);
    itVector.outPut("itArr after addTail() call");
    
    cout << "Testing template class using long" << endl;
    InitArray(lgArr, ARR_SIZE, -10000L, 10000L);
    Vector<long> lgVector(lgArr, ARR_SIZE);
    lgVector.outPut("lgVector before delHead() call");
    lgSingle = lgVector.delHead();
    lgVector.outPut("lgVector after delHead() call");
    lgVector.addTail(&lgSingle);
    lgVector.outPut("lgVector after addTail() call");
    
    cout << "Testing template class using short" << endl;
    InitArray(shArr, ARR_SIZE, static_cast<short>(-100), static_cast<short>(100));
    Vector<short> shVector(shArr, ARR_SIZE);
    shVector.outPut("shVector before delHead() call");
    shSingle = shVector.delHead();
    shVector.outPut("shVector after delHead() call");
    shVector.addTail(&shSingle);
    shVector.outPut("shVector after addTail() call");

    cout << "Testing template class using float" << endl;
    InitArray(flArr, ARR_SIZE, -100000.f, 10000.f);
    Vector<float> flVector(flArr, ARR_SIZE);
    flVector.outPut("flVector before delHead() call");
    flSingle = flVector.delHead();
    flVector.outPut("flVector after delHead() call");
    flVector.addTail(&flSingle);
    flVector.outPut("flVector after addTail() call");

    cout << "Testing template class using double" << endl;
    InitArray(dbArr, ARR_SIZE, static_cast<double>(-1.05e6), static_cast<double>(1.05e6));
    Vector<double> dbVector(dbArr, ARR_SIZE);
    dbVector.outPut("dbVector before delHead() call");
    dbSingle = dbVector.delHead();
    dbVector.outPut("dbVector after delHead() call");
    dbVector.addTail(&dbSingle);
    dbVector.outPut("dbVector after addTail() call");

    cout << "Testing template class using Rational custom class" << endl;
    InitArray(raArr, ARR_SIZE, Rational(-100, -100), Rational(100, 100));
    Vector<Rational> raVector(raArr, ARR_SIZE);
    raVector.outPut("raVector before delHead() call");
    raSingle = raVector.delHead();
    raVector.outPut("raVector after delHead() call");
    raVector.addTail(&raSingle);
    raVector.outPut("raVector after addTail() call");

   return 0;
}
