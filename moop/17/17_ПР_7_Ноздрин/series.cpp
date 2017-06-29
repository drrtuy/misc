#include <iostream>
#include <math.h>

#include "series.h"

using namespace std;

        //double _delta;
        //double _first; 

std::ostream &operator<<(std::ostream &ostream, const Linear &obj)
{
    ostream << "First elem value: " << obj._first << " Delta value: " << obj._delta << " ";
    return ostream;
}

Linear::Linear()
{
    _delta = 0.0;
    _first = 0.0;
}

Linear::~Linear()
{
    _delta = 0.0;
    _first = 0.0;
}

//
// Конструктор арифметической прогрессии
//
Linear::Linear(double first, double delta)
{
    _first = first;
    _delta = delta;
}

//
// Функция получения n-ого члена арифметической прогрессии.
//
double Linear::nthMember(int numb)
{
    return _first + (numb-1) * _delta;
}

double Linear::sum(int numb)
{
    double nth = _first + (numb - 1) * _delta;
    return numb * (_first + nth) / 2;
}

std::ostream &operator<<(std::ostream &ostream, const Exp &obj)
{
    ostream << "First elem value: " << obj._first << " Delta value: " << obj._delta << " ";
    return ostream;
}

Exp::Exp()
{
    _first = 0.0;
    _delta = 0.0;
}

Exp::~Exp()
{
    _first = 0.0;
    _delta = 0.0;
}

Exp::Exp(double first, double delta)
{
    _first = first;
    _delta = delta;
}

double Exp::nthMember(int numb)
{
    return _first*pow(_delta, static_cast<double>(numb));
}

double Exp::sum(int numb)
{
    return _first*(1-pow(_delta, static_cast<double>(numb)))/(1-_delta);
}
