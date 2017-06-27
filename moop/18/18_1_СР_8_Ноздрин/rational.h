#ifndef HRATIONAL

#include <iostream>
#define HRATIONAL
#define MAX_LEN 64

//
// Класс для представления рациональных чисел. Внутренее представление
// числитель и знаменатель signed int-ы.
//
class Rational
{
    private:
        int _nom;
        int _denom;
    public:
        Rational();
        Rational(int nom, int denom);
        Rational(const Rational &Operand);
        ~Rational();

        void outPut();
        int getNom();
        int getDenom();
/*
        Rational &operator+(const Rational &Operand);
        Rational &operator-(const Rational &Operand);
        Rational &operator*(const Rational &Operand);
        Rational &operator/(const Rational &Operand);
        bool operator<(const Rational &Operand);
*/
        bool operator>(const Rational &Operand);

        friend std::ostream &operator<<(std::ostream &stream, const Rational &Operand);
};

#endif
