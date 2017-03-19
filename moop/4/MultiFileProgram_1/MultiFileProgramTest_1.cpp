#include <iostream>
#include <locale>

#include "MultiFileProgram_1.h"

using std::cout;
using std::endl;

int getDigitSum(int a);

int main ()
{

    int sum = 0;

    setlocale(LC_ALL, " ");

    for (int i = 1; i <= 27; i++){
        cout << "Числа с суммой цифр:" << i << "--------------" << endl;
        for (int it = 100; it <= 999; it++){
            if ((sum = getDigitSum(it)) == i) {
                cout << it << endl;
            } 
        }
    }

    return 0;
}
