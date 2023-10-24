// acwing 11 背包问题求方案数
/*
    f[i][j]表示前i个物品，体积不超过j的最大值
    g[i][j]表示前i个物品，体积不超过j的最大价值对应的方案数
    f[i][j] = max(f[i-1][j], f[i-1][j-v] + w)
    如果f[i-1][j] > f[i-1][j-v]+w,  g[i][j] = g[i-1][j]
    如果f[i-1][j] < f[i-1][j-v]+w,  g[i][j] = g[i-1][j-v]
    如果f[i-1][j] == f[i-1][j-v]+w,  g[i][j] = g[i-1][j] + g[i-1][j-v]
*/
/*
#include <iostream>
using namespace std;

const int N = 1010, MOD = 1e9 + 7;
int f[N], g[N];
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 0; i <= m; i++)
        g[i] = 1;   // 相当于g[0][i]=1，前0个物品，体积不超过i的最优方案数为1
    for (int i = 1; i <= n; i++)
    {
        int v, w;
        cin >> v >> w;
        for (int j = m; j >= v; j--)
        { 
            if (f[j] < f[j - v] + w)
                g[j] = g[j - v] % MOD;
            else if (f[j] == f[j - v] + w)
                g[j] = (g[j] + g[j - v]) % MOD;
            f[j] = max(f[j], f[j - v] + w);
        }
    }

    cout << g[m] << endl;

    return 0;
}*/

/*
    f[i][j]表示前i个物品，体积刚好为j的最大值
    g[i][j]表示前i个物品，体积刚好为j的最大价值对应的方案数
    f[i][j] = max(f[i-1][j], f[i-1][j-v] + w)
    如果f[i-1][j] > f[i-1][j-v]+w,  g[i][j] = g[i-1][j]
    如果f[i-1][j] < f[i-1][j-v]+w,  g[i][j] = g[i-1][j-v]
    如果f[i-1][j] == f[i-1][j-v]+w,  g[i][j] = g[i-1][j] + g[i-1][j-v]
*/
#include <iostream>
#include <cstring>
using namespace std;

const int N = 1010, MOD = 1e9 + 7;
int f[N], g[N];
int n, m;

int main()
{
    cin >> n >> m;
    memset(f, -0x3f, sizeof f);
    f[0] = 0;
    g[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        int v, w;
        cin >> v >> w;
        for (int j = m; j >= v; j--)
        {
            if (f[j] < f[j - v] + w)
                g[j] = g[j - v] % MOD;
            else if (f[j] == f[j - v] + w)
                g[j] = (g[j] + g[j - v]) % MOD;
            f[j] = max(f[j], f[j - v] + w);
        }
    }

    int res = 0;
    for (int i = 0; i <= m; i++)
        res = max(res, f[i]);
    int cnt = 0;
    for (int i = 0; i <= m; i++)
        if (f[i] == res)
            cnt = (cnt + g[i]) % MOD;

    cout << cnt << endl;

    return 0;

}