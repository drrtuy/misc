#include <clocale>
#include <iostream>
#include <vector>

using  namespace std;

#define HAND_SIZE 5

typedef struct {
    int firstComb;
    int secComb;
    int sum;
} combinations_t;

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


int getOutput(vector<int> hand) {
    int result = 7;
    int counter;
    combinations_t *combinations;

    vector<int> counters; 

    for (int i = 0; i <= HAND_SIZE - 1; i++) {
        counter = 1;
        for (int it = i + 1; it <= HAND_SIZE; it++) {
            if ((hand[it] != 0) && (hand[i] == hand[it])) {
                counter++;
                hand[it] = 0;
            }
        } 

        if ((counter == 5) || (counter == 4)) { 
            return 1; 
        }

        counters.push_back(counter);
    }

    combinations = getBestCombinations(counters);

    if (combinations->sum == 5) { //фул хаус
        result = 3;
    } else if (combinations->firstComb == 3) { //тройка
        result = 4;
    } else if (combinations->sum == 4) { //пара пар
        result = 5;
    } else if (combinations->sum == 3) { //пара
        result = 6;
    }  

    /*
    for (int o: counters) {
        cout << "счётчик " << o << endl;
    }
    */

    return result;
}

combinations_t *getBestCombinations(vector<int> counters) {
    combinations_t *result;

    result = new combinations_t;
    result->firstComb = 1;
    result->secComb = 1;

    for (int c: counters) {
        if (c > result->firstComb ) {
            result->secComb = result->firstComb;
            result->firstComb = c;
        } else if (c > result->secComb) {
            result->secComb = c; 
        }
    }

    result->sum = result->firstComb + result->secComb;

    /*cout << "first: " << result->firstComb << " second: " <<\
 result->secComb << " sum: " << result->sum << endl;
    */
    
    return result;
}
