#include <iostream>

using namespace std;
int main()
{
    //
    ios_base::sync_with_stdio(false);
    uint64_t numberOfSets = 0;
    uint64_t dist = 0;

    cin >> numberOfSets;
    for (uint64_t i = 1; i <= numberOfSets; i++) {
        cin >> dist;
        uint64_t d1 = 1;
        uint64_t d2 = d1 + dist;
        uint64_t d3 = d2 + dist;
        uint64_t potentialResult = d1 * d2 * d3;
        if (potentialResult - d3 >= dist) {
            cout << potentialResult << "\n";
        } else {
            cout << d1 * d2 * d3 * (d3 + dist) << "\n";
        }
    }
}
