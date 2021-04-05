#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);
    getline(cin, s);
    string::size_type maxSize = 0;
    string maxWord;
    string word;

    istringstream is(s);
    while (is >> word)
    {
        if (maxSize < word.size())
        { 
            maxSize = word.size();
            maxWord = word;
        }           
    }

    cout << maxWord << "\n";
    cout << maxSize << "\n";
}
