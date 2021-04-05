#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    ifstream iFile("input.txt");
    ofstream oFile("output.txt");

    string number;
    iFile >> number;

    if (number.size() == 1) {
        oFile << number;
    } else { 
        if (number[0] == '-') {
            oFile << '-';
        }
        auto strIter = number.end() - 1;

        while (strIter >= number.begin() && *strIter == '0')
            strIter--;

        while (strIter >= number.begin()) {
            if (*strIter == '-') {
                break;
            }
            oFile << *strIter--;
        }
    }

    oFile << "\n";
}
