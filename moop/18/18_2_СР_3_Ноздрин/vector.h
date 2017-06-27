#ifndef HVECTOR

#define HVECTOR

template<class T>
class Vector {
    private:
        T *array;
        int size;
    public:
        Vector(); 
        Vector(T *array, int size);
        Vector(const Vector &vec); 
        ~Vector(); 
        void outPut(const char* msg);
        void outPut(const char* msg) const;
        T &delHead();
        void addTail(T*);
        Vector& operator=(const Vector &vec);
};

#include "vector.cpp"

#endif
