#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);

    if (s.length() == 1)
    {
        cout << "True" << "\n";
        exit(0);
    }

    auto i1 = s.begin();
    auto i2 = s.end(); i2--;

    for (string::size_type i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }

    while(isalnum(*i1) == 0 && i1 < s.end())
        i1++;
    while(isalnum(*i2) == 0 && i2 > s.begin()-1)
        i2--;

    // main compare loop
    while (i1 < s.end() && i2 > s.begin()-1)
    {
        if (*i1 != *i2)
            break;
        i1++; i2--;
        while(isalnum(*i1) == 0 && i1 < s.end())
            i1++;
        while(isalnum(*i2) == 0 && i2 > s.begin()-1)
            i2--;
    }

    // final decision
    if (i1 != s.end() && i2 != s.begin() - 1)
       cout << "False";
    else
       cout << "True";

    cout << "\n";
}
