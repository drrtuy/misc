#ifndef H_SORT

#define H_SORT
#include "rational.h"
#define ARR_SIZE 5

template <class T>
void InitArray(T *array, int size, T genMinVal, T genMaxVal);
template <class T>
void outPut(const char *msg, T *array, int size);
template <class T>
void doBubbleSort(T *array, int size);
void InitArray(Rational *array, int size, int genMinNom, int genMaxDenom);

#include "sort.cpp"

#endif
