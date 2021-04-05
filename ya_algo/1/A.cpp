#include <iostream>

using namespace std;
int main()
{
    //
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int32_t a, b, c, x;
    cin >> a; cin >> x; cin >> b; cin >> c;
    cout << a * x * x + b * x + c << "\n";
}
