#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string op1, op2, result;
    getline(cin, op1);
    getline(cin, op2);
    const string& longest = (op1.length() > op2.length()) ? op1 : op2;
    const string& shortest = (op1.length() > op2.length()) ? op2 : op1;
    result.reserve(longest.length() + 1);
    uint8_t extra = 0;
    string::size_type lengthDiff = longest.length() - shortest.length();
    for(string::size_type i = shortest.length(); i > 0; i--)
    {
        int8_t r = shortest[i-1] + longest[i + lengthDiff - 1] + extra;
        switch (r)
        {
            case 96:
                result.push_back('0');
                break;
            case 97:
                result.push_back('1');
                extra = 0;
                break;
            case 98:
                result.push_back('0');
                extra = 1;
                break;
            default:
                result.push_back('1');
                extra = 1;
                break;
        }
    }

    if (longest.length() != shortest.length())
    {
        for (string::size_type i = lengthDiff; i > 0; i--)
        {
            int8_t r = longest[i-1] + extra;
            switch (r)
            {
                case 48:
                    result.push_back('0');
                    break;
                case 49:
                    result.push_back('1');
                    extra = 0;
                    break;
                default:
                    result.push_back('0');
                    extra = 1;
                    break;
            }
        } 
    }

    if (extra)
    {
        result.push_back('1');
    }
    
    {
        auto a = result.end(); a--;
        while(a >= result.begin())
        {
            cout << *a; a--;
        }
        cout << "\n";
    }

}
