#include <vector>

using std::vector;

#define HAND_SIZE 5

typedef struct {
    int firstComb;
    int secComb;
    int sum;
} combinations_t;

combinations_t *getBestCombinations(vector<int> counters);
int getOutput(vector<int> hand);
