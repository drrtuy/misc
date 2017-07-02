#ifndef HARRAY

#define HARRAY

#include <iostream>
#define ARR_SIZE 5

void initArray(int *array, int size, int genMinVal, int genMaxVal);

class Array
{
    protected:
        int *_array;
        int _size;
    public:
        int *getArray() const;
        int getSize()const;
        virtual void sum(const Array &right) = 0;
        virtual void foreach() = 0;
};

class SortArray: protected Array
{
    public:
        SortArray();
        SortArray(int size);
        SortArray(int *data, int size);
        ~SortArray();
        void sum(const Array &right);
        void foreach();
    friend std::ostream &operator<<(std::ostream&, const SortArray&);
};

#endif
