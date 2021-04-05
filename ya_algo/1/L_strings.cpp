#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string op1, op2, result;
    getline(cin, op1);
    getline(cin, op2);
    sort(op1.begin(), op1.end(), less<char>());
    sort(op2.begin(), op2.end(), less<char>());
    const string& longest = op2;
    const string& shortest = op1;
    bool found = false;

    for(uint16_t i = 0; !found && i < shortest.length(); i++)
    {
        if(shortest[i] != longest[i])
        {
            cout << longest[i];
            found = true;
        }
    }

    if (!found)
        cout << longest[longest.length() - 1];
   
    cout << "\n"; 
}
