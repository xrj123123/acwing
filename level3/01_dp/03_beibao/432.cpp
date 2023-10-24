// acwing 432 采药
#include <iostream>
using namespace std;

const int N = 1010;
int t[N], v[N];
int f[N];
int n, m;   // m是时间, n是草药数量

int main()
{
    cin >> m >> n;

    for (int i = 1; i <= n; i++)
        cin >> t[i] >> v[i];
    
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= t[i]; j--)
            f[j] = max(f[j], f[j - t[i]] + v[i]);

    cout << f[m] << endl;

    return 0;
}