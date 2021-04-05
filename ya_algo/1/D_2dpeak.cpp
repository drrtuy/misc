#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    uint32_t n = 0;
    cin >> n;
    vector<int32_t> vec;
    vec.reserve(n);
    int32_t tmp = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> tmp;
        vec.push_back(tmp);
    }

    if (n == 1)
    {
        cout << "1" << "\n";
        exit(0);
    }
    else if (n == 2)
    {
        if (vec[0] != vec[1])
            cout << "1" << "\n";
        else
            cout << "0" << "\n";
        exit(0);
    }

    uint32_t resultCounter = (vec[0] > vec[1]) ? 1 : 0;
    for(uint32_t i = 1; i < n - 1; i++)
    {
        if (vec[i - 1] < vec[i] && vec[i + 1] < vec[i])
            resultCounter++; 
    }

    resultCounter = (vec[n - 1] > vec [n - 2]) ? resultCounter + 1 : resultCounter;
    
    cout << resultCounter << "\n"; 
}
