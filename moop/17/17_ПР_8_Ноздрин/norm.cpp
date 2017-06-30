#include <iostream>
#include <cmath>

#include "norm.h"
using namespace std;

//
// Класс для комплексных чисел.
//
Complex::Complex()
{
    _im = 0.0;
    _re = 0.0;
}

Complex::~Complex()
{
    _im = 0.0;
    _re = 0.0;
}

Complex::Complex(double im, double real)
{
    _im = im;
    _re = real;
}

double Complex::getNorm()
{
    return sqrt(pow(_im, 2.0)+pow(_re, 2.0)); 
}

double Complex::getModulo()
{
    return pow(this->getNorm(), 2.0);    
}

std::ostream &operator<<(std::ostream& ostream, const Complex& obj)
{
    ostream << "Complex number with im: " << obj._im << " real: " << obj._re << " ";
    return ostream;
}

Vector3D::Vector3D()
{
    _x = 0.0;
    _y = 0.0;
    _z = 0.0;
} 

Vector3D::~Vector3D()
{
    _x = 0.0;
    _y = 0.0;
    _z = 0.0;
} 

Vector3D::Vector3D(double x, double y, double z)
{
    _x = x;
    _y = y;
    _z = z;
}

double Vector3D::getNorm()
{
    return max(abs(_x), max(abs(_y), abs(_z)));
}

double Vector3D::getModulo()
{
    return sqrt(pow(_x, 2.0)+pow(_y, 2.0)+pow(_z, 2.0));
} 

std::ostream &operator<<(std::ostream &ostream, const Vector3D &obj)
{
    ostream << "Vector3D coordinates x: " << obj._x << " y: " << obj._y << " z: " << obj._z << " ";
    return ostream;
} 
