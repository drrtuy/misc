#include <iostream>

using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    uint16_t n = 0, pow = 1;
    cin >> n;

    while(pow < n)
    {
        pow *= 4; 
    }

    if (pow == n || n == 1)
        cout << "True";
    else
        cout << "False";
    
    cout << "\n";
}
