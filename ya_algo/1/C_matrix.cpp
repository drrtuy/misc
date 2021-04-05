#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
using Matrix = vector<vector<T>>;
using targetType = int16_t;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Matrix<targetType> M;
    targetType n, m, tmp;
    cin >> n; cin >> m;
    if (!n && !m)
    {
        cout << "\n";
        exit(0);
    }
    M.reserve(n);
    for(targetType i = 0; i < n; i++)
    {
        M.push_back({});
        M[i].reserve(m);
        for(targetType it = 0; it < m; it++)
        {
            cin >> tmp;
            M[i].push_back(tmp);
        }
    }
    targetType targetN, targetM;
    cin >> targetN; cin >> targetM;
    
    vector<targetType> neighbors;
    if (targetN == 0)
    {
        if (n != 1)
            neighbors.push_back(M[1][targetM]);
    }
    else if (targetN == n - 1)
    {
        if (n != 1)
            neighbors.push_back(M[n - 2][targetM]);
    }
    else
    {
        neighbors.push_back(M[targetN - 1][targetM]);
        neighbors.push_back(M[targetN + 1][targetM]);
    }

    if (targetM == 0)
    {
        if (m != 1)
            neighbors.push_back(M[targetN][1]);
    }
    else if (targetM == m - 1)
    {
        if (m != 1)
            neighbors.push_back(M[targetN][m - 2]);
    }
    else
    {
        neighbors.push_back(M[targetN][targetM - 1]);
        neighbors.push_back(M[targetN][targetM + 1]);
    }
    sort(neighbors.begin(), neighbors.end(), less<targetType>());
    for(auto el : neighbors)
        cout << el << " ";   
    cout << "\n"; 

}
