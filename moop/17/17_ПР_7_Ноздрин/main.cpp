#include <iostream>

#include "series.h"

using namespace std;

int main()
{
    Linear lin(1.0, 2.5);

    cout << "--------Linear progression testing---------" << endl;
    cout << "5th member of a linear progression " << lin << " = " << lin.nthMember(5) << endl;
    cout << "Sum of the linear progression " << lin << " up to the 5th member = " << lin.sum(5) << endl;

    Exp exp(1.0, 2.0);

    cout << "--------Exp progression testing---------" << endl;
    cout << "5th member of an exp progression " << exp << " = " << exp.nthMember(5) << endl;
    cout << "Sum of the exp progression " << exp << " up to the 5th member = " << exp.sum(5) << endl;


    return 0;
}
