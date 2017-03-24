#include <iostream>

#include "module.h"

using namespace std;

int main ()
{
    char buf[BUF_LEN + 1];

    cout << "Enter an ASCII text" << endl;
    cin.getline(buf, BUF_LEN);

    cout << "The text after braces modification:" << endl;
    cout << convert(buf) << endl;

    return 0;
}
