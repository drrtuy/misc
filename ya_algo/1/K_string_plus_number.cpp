#include <iostream>
#include <vector>

using namespace std;

uint32_t numberFromString(string& src)
{
    return 1;
}

const uint32_t pow10[] =
{
    0,
    1,
    10,
    100,
    1000,
    10000,
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    uint32_t k = 0, n = 0, tmp = 0, x = 0;
    cin >> n;
    for (uint8_t i = n; i > 0; i--)
    {
        cin >> tmp;
        x += tmp * pow10[i];
    }
    cin >> k;

    uint32_t sum = x + k;
    uint32_t prevQuotinent = 0;
    vector<uint32_t> result;
    while (sum > 0)
    {
        prevQuotinent = sum;
        sum /= 10;
        result.push_back(prevQuotinent - sum * 10);         
    }

    if (!result.empty())
    {
        auto a = result.end(); a--;
        while(a >= result.begin())
        {
            cout << *a << " "; a--;
        }
        cout << "\n";
    }
    else
    {
        cout << "0" << "\n";
    }
}
