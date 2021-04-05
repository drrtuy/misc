#include <iostream>
#include <string>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    uint16_t input;
    cin >> input;
    if (input == 0)
    {
        cout << "0";
        exit(0);
    }
    if (input == 1)
    {
        cout << "1";
        exit(0);
    }

    string s;
    uint16_t input1 = input;
    while (input > 0)
    {
        input >>= 1;
        if (input1 - input * 2)
        {
            s.push_back('1');
        }
        else
        {
            s.push_back('0');
        }
        input1 = input;
    }
 
    auto a = s.end(); a--;
    while(a >= s.begin())
    {
        cout << *a; a--;
    }
    cout << "\n";
}
