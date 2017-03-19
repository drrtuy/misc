#include <iostream>
#include <locale>

using std::cout;
using std::endl;

int main ()
{

    setlocale(LC_ALL, " ");

    for (int i = 0; i <= 9; i++){
        cout << "-------------" << i << "--------------" << endl;
        for (int it = 0; it <= 9; it++){
            cout << i << " * " << it << " = " << it * i << endl;
        }
    }

    return 0;
}
