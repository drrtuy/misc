#include <iostream>

#include "norm.h"

using namespace std;

int main()
{
    Complex comp(1.0, 1.0);
    cout << "--------Complex number testing---------" << endl;
    cout << comp << " norm: " << comp.getNorm() << " modulo: " << comp.getModulo() << endl;

    Vector3D vec(2.0, 3.0, 4.0);
    cout << "--------3D Vector class testing---------" << endl;
    cout << vec << " norm: " << vec.getNorm() << " modulo: " << vec.getModulo() << endl;

    return 0;
}
