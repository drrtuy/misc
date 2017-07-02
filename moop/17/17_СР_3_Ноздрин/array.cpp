#include <random>
#include <iostream>

#include "array.h"

using namespace std;

void initArray(int *array, int size, int genMinVal, int genMaxVal)
{
    double d;
    for(int i = 0; i < size; i++){
        d = float(RAND_MAX - rand()) / RAND_MAX;
        array[i] = int(d * (genMaxVal - genMinVal));
    }
}

int *Array::getArray() const
{
    return _array;
}

int Array::getSize() const
{
    return _size;
}

SortArray::SortArray()
{
    _array = NULL;
    _size = 0;
}

SortArray::SortArray(int size)
{
    _array = new int[size];
    _size = size;
}

SortArray::SortArray(int *data, int size)
{
    _array = data;
    _size = size;
}

SortArray::~SortArray()
{
    if(_size)
        delete [] _array;
    _array = NULL;
    _size = 0;
}

void SortArray::sum(const Array &right)
{
    int newSize = this->_size + right.getSize();
    int *tmp = new int[newSize];
    int *rightArray = right.getArray();
    int rightSize = right.getSize();
    int i = 0;
    for(; i < this->_size; i++)
        tmp[i] = this->_array[i];
    for(i = 0; i < rightSize; i++)
        tmp[i+this->_size] = rightArray[i];

    if (this->_size)
        delete [] this->_array;
    
    this->_array = tmp;
    this->_size = newSize;
}

void SortArray::foreach()
{
    return;
}

ostream &operator<<(ostream &ostream, const SortArray &obj)
{
    ostream << "SortArray with " << obj._size << " elements: ";
    for(int i = 0; i < obj._size; i++)
        ostream << obj._array[i] << " ";
    return ostream;
}
