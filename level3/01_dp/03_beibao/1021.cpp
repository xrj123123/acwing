// acwing 1021 货币系统
/*
    完全背包求方案数
    f[i][j]表示前i张纸币，面值恰好为j的方案数
    f[i][j] = f[i-1][j] + f[i][j-a]
*/
#include <iostream>
using namespace std;
typedef long long ll;

const int N = 3010;
ll f[N];
int n, m;

int main()
{
    cin >> n >> m;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        for (int j = a; j <= m; j++)
            f[j] += f[j - a];
    }

    cout << f[m] << endl;

    return 0;
}
