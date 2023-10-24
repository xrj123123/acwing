// acwing 9 分组背包问题
/*
    多重背包是第i个物品选几个
    分组背包是第i组物品选哪个
*/
/*#include <iostream>
using namespace std;
const int N = 110;
int v[N][N], w[N][N], s[N];
int f[N][N];
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        for (int j = 0; j < s[i]; j++)
            cin >> v[i][j] >> w[i][j];
    }

    for (int i = 1; i <= n; i++) // n组数据
        for (int j = 0; j <= m; j++)
        {
            f[i][j] = f[i - 1][j];
            for (int k = 0; k < s[i]; k++) // 第i组数据中的第k个数据
            {
                if (v[i][k] <= j)
                    f[i][j] = max(f[i][j], f[i - 1][j - v[i][k]] + w[i][k]);
            }
        }

    cout << f[n][m] << endl;
    return 0;
}*/

// 一维优化
#include <iostream>
using namespace std;
const int N = 110;
int v[N][N], w[N][N], s[N];
int f[N];
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        for (int j = 0; j < s[i]; j++)
            cin >> v[i][j] >> w[i][j];
    }

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--)
            for (int k = 0; k < s[i]; k++)
                if (v[i][k] <= j)
                    f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);

    cout << f[m] << endl;
    return 0;
}