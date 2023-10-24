// acwing 1024 装箱问题
#include <iostream>
using namespace std;

const int N = 20010;
int v[N], f[N];
int n, m;

int main()
{
    cin >> m;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i];

    for (int i = 0; i < n; i++)
        for (int j = m; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + v[i]);
        
    cout << m - f[m] << endl;

    return 0;
}