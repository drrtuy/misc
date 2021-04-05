#include <iostream>
#include <string>

using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int32_t a, b, c;
    cin >> a; cin >> b; cin >> c;
    if (1 & a & b & c || !(1 & (a | b | c)) )
        cout << "WIN";
    else
        cout << "FAIL";
    cout << "\n";
}
