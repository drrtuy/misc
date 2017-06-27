#include <iostream>
#include <random>

#include "rational.h"
#define ARR_SIZE 5

using namespace std;

template <class T>
void InitArray(T *array, int size, T genMinVal, T genMaxVal)
{
    double d;
    for(int i = 0; i < size; i++){
        d = float(RAND_MAX - rand()) / RAND_MAX;
        array[i] = T(d * (genMaxVal - genMinVal));
    }
}

template <>
void InitArray(Rational *array, int size, Rational genMinVal, Rational genMaxVal)
{
    double d;
    int nom, denom;
    
    for(int i = 0; i < size; i++){
        d = float(RAND_MAX - rand()) / RAND_MAX;
        nom = int(d * genMaxVal.getNom() - genMinVal.getNom());
        d = float(RAND_MAX - rand()) / RAND_MAX;
        denom = int(d * genMaxVal.getDenom() - genMinVal.getDenom());
        array[i] = Rational(nom, denom); 
    }
}


template <class T>
void outPut(const char *msg, T *array, int size)
{
    for(int i = 0; i < size; i++)
        cout << array[i] << endl;
    cout << endl;

}

template <class T>
void doBubbleSort(T *array, int size)
{    
    T buf, iterMax;
    int endInd = size-1;
    int i, it, iterMaxInd;
    for(i = 0; i<=size-2; i++){
        iterMax = array[endInd];
        iterMaxInd = endInd;
        for(it = endInd-1; it>=i; it--){
            if(array[it] > iterMax){
                iterMax = array[it];
                iterMaxInd = it; 
            }
        }
       buf=array[i]; array[i]=iterMax; array[iterMaxInd]=buf; 
    }
}
