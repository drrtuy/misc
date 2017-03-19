#include <iostream>
#include <locale>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;

int main ()
{
    int m = 1, n, root, ones;
    bool simple;

    setlocale(LC_ALL, " ");
    
    cout << "Введите два int-а: N и M, N < M < 1000." << endl;
    cin >> n;
    cin >> m;

    for (int i = n; i <= m; i++) {
        simple = true;
        if ((i == 2) || (i == 5)) {
            cout << "Очередное простое число: " << i << endl; 
            continue;
        }
        ones = i % 10;
        //cout << "ones: " << ones << endl;
        if ((ones != 1) && (ones != 3) && (ones != 7) && (ones != 9))
            continue;

        //cout << "i: " << i << endl;
 
        root = sqrt(i) + 1;
        //cout << "root: " << root << endl;
        for (int it = 2; it <= root; it++) {
            if ((i % it) == 0) {
                simple = false;
                break;
            }
        }      
        if (simple == true) {
            cout << "Очередное простое число: " << i << endl; 
        }

    }

    return 0;
}
