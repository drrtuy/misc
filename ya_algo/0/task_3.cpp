#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    uint64_t numberOfSets = 0;

    cin >> numberOfSets;
    for (uint64_t i = 1; i <= numberOfSets; i++) {
        uint64_t n = 0; uint64_t tmp = 0;
        cin >> n;
        vector<uint64_t> src;
        for (uint64_t it = 1; it <= 2*n; it++) {
            cin >> tmp;
            src.push_back(tmp);
        }

        sort(src.begin(), src.end(), less<uint64_t>());

        for(uint64_t el: src) {
            cout << el << " ";
            cout << "\n";
        }
    }
}
