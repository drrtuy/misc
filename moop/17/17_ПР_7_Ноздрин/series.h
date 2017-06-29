#ifndef HSERIES

#define HSERIES
#include <iostream>

//
// Абстрактный класс прогрессии. Модель задаётся первым членом и дельтой.
//
class Series 
{
   protected:
        double _delta;
        double _first; 
   public:
        virtual double nthMember(int) = 0;
        virtual double sum(int) = 0;
};

//
// Арифметическая прогрессия. 
//
class Linear: protected Series
{
   public: 
        Linear();
        ~Linear();
        Linear(double first, double delta);
        double nthMember(int numb);
        double sum(int numb);
    friend std::ostream &operator<<(std::ostream &ostream, const Linear &obj); 
};
//
// Геометрическая прогрессия.
//
class Exp: public Series
{
   public:
        Exp();
        ~Exp();
        Exp(double first, double delta);
        double nthMember(int numb);
        double sum(int numb);
    friend std::ostream &operator<<(std::ostream &ostream, const Exp &obj); 
};

#endif
