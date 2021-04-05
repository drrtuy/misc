#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
using uint16_t = unsigned short int;
using int16_t = short int;

int main()
{
    ios_base::sync_with_stdio(false);
    ifstream iFile("input.txt");
    ofstream oFile("output.txt");

    int targetNumber = 0;
    iFile >> targetNumber;
    int number = 0;
    vector<int> numbers;
    numbers.reserve(5000);
    while (iFile >> number) {
        numbers.push_back(number);
    }
    
//    cout << numbers.size() << "\n";
//    cout << "first " << numbers[0] << " last " << numbers[numbers.size()-1] << "\n";
    sort(numbers.begin(), numbers.end(), less<int>());
//    cout << "first " << numbers[0] << " last " << numbers[numbers.size()-1] << "\n";

    int distance = 0;
    int sum = 0;
    int bestSum = 200001;
    int bestDistance = -200001;
    
//    copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
//    cout << "\n";

    for (uint16_t i = 0; bestDistance && i < numbers.size() - 2; i++) {
        uint16_t j = i + 1;
        uint16_t k = numbers.size() - 1;
        while (j < k) {
            sum = numbers[i] + numbers[j] + numbers[k];
            distance = sum - targetNumber;
//            cout << " at " << i << " " << j << " " << k << "\n";
//            cout << "distance " << distance << "\n";
//            cout << "sum " << sum << "\n";
            if (!distance) {
                bestDistance = distance;
                bestSum = sum;
//                cout << " perfect match at " << i << " " << j << " " << k << "\n";
                break;
            } else if (distance > 0)
                k--;
            else
                j++;
            
            if (abs(distance) < abs(bestDistance))
                bestSum = sum;
        }
    }

    oFile << bestSum;
    oFile << "\n";
}
