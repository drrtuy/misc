#include <iostream>

using namespace std;

template<class T> Vector<T>::Vector()
{
    size = 0;
    array = NULL;
}

template<class T> Vector<T>::Vector(T* ar, int _size)
{
    array = new T[_size];
    for ( int i = 0; i < _size; i++ )
        array[i] = ar[i];
    size = _size;
}

template<class T> Vector<T>::Vector(const Vector<T> &vec) {
    size = vec.size;
    array = new T[size];
    for ( int i = 0; i < size; i++ )
        array[i] = vec.array[i];
}

template<class T> Vector<T>::~Vector() {
    if ( array != NULL )
    {
        delete[] array;
        array = NULL;
        size = 0;
    }
}

template<class T> void Vector<T>::outPut(const char* msg) {
    cout << msg << ": ";
    for ( int i = 0; i < size; ++i )
        cout << array[i] << ",\t";
    cout << endl;
}

template<class T> void Vector<T>::outPut(const char* msg) const
{
    cout << msg << ": ";
    for ( int i = 0; i < size; ++i )
        cout << array[i] << ",\t";
    cout << endl;
}

template<class T> Vector<T>& Vector<T>::operator=(const Vector<T> &vec)
{
    if ( this != &vec ) 
    {
        if ( size != vec.size )
        {
            delete[] array;
            size = vec.size;
            array = new T[size];
        }
        for ( int i = 0; i < size; ++i )
            array[i] = vec.array[i];
    }
    return *this;
}

template<class T> T &Vector<T>::delHead()
{

    T *elBuf = new T;
    *elBuf = this->array[0];

    if(this->size == 1){
        this->size = 0;
        delete[] this->array;
        this->array = NULL;
        cout << "No elements left, effectively erase the Vector instance" << endl;
    } else {
        int newSize=size-1;
        T *buf = new T[newSize];
        for(int i = 1; i < this->size; i++)
            buf[i-1] = this->array[i];
        this->size = newSize;
        delete[] this->array;
        this->array = buf;
    }
    return *elBuf;
}

template<class T> void Vector<T>::addTail(T *tail)
{
    T *buf = new T[this->size+1];
    for(int i=0; i <= this->size; i++)
        buf[i] = this->array[i];
    buf[this->size] = *tail;
    this->size = this->size+1;
    delete[] this->array;
    this->array = buf;
}

