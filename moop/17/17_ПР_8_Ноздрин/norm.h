#ifndef HNORM

#define HNORM

#include <iostream>

class Norm
{
    public:
        virtual double getNorm() = 0;
        virtual double getModulo() = 0;
};

//
// Класс для комплексных чисел.
//
class Complex: public Norm
{
    private:
        double _im;
        double _re;
    public:
        Complex();
        ~Complex();
        Complex(double im, double real);
        double getNorm();
        double getModulo(); 
    friend std::ostream &operator<<(std::ostream&, const Complex&);
};

class Vector3D: public Norm
{
    private:
        double _x;
        double _y;
        double _z;
    public:
        Vector3D();
        ~Vector3D();
        Vector3D(double x, double y, double z);
        double getNorm();
        double getModulo(); 
    friend std::ostream &operator<<(std::ostream&, const Vector3D&);
};



#endif
