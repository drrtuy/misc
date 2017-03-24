#include <locale.h>
#include <time.h>
#include <iostream>
#include <string.h>

#include "module.h"

using std::cout;
using std::cin;
using std::endl;

int main ()
{
    char buf[BUF_LEN + 1];

    cout << "Enter an ASCII string." << endl;
    cin.getline(buf, BUF_LEN);
    cout << "Given string " << buf << endl;
    cout << "Number of digits: " << countDigits((char *) buf) << endl;

    return 0;
}
