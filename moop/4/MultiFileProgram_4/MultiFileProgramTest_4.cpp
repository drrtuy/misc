#include <clocale>
#include <iostream>

#include "MultiFileProgram_4.h"

using namespace std;

combinations_t *getBestCombinations(vector<int> counters);
int getOutput(vector<int> hand);

int main() 
{
    int output, input, it = 0;
    vector<int> hand;

    setlocale(LC_ALL, ""); 
    cout << "Введите 5 int-ов для задания карт руки" << endl;
    while ((it++ < 5) && (cin >> input)) {
        hand.push_back(input);
    }

    output = getOutput(hand);
   
    cout << "Результат: " << output << endl;

    return 0;

}
