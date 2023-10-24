// acwing 1013 机器分配
/*
    分组背包 + 背包问题求具体方案数
    可以将每个公司分配的台数看做一组物品，因为每一个公司只能选一种方案
    题目没有要求字典序最小，因此不需要逆序求
*/
#include <iostream>
using namespace std;

const int N = 11, M = 16;
int w[N][M], f[N][M];
int way[N];
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> w[i][j];
    
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
        {
            f[i][j]  = f[i - 1][j];
            for (int k = 1; k <= j; k++)
                f[i][j] = max(f[i][j], f[i - 1][j - k] + w[i][k]);
        }

    cout << f[n][m] << endl;

    // 求具体方案
    int j = m;
    for (int i = n; i >= 1; i--)
        for (int k = 0; k <= j; k++)
            if (k <= j && f[i][j] == f[i - 1][j - k] + w[i][k])
            {
                way[i] = k;
                j -= k;
                break;
            }

    for (int i = 1; i <= n; i++)
        cout << i << " " << way[i] << endl;

    return 0;
}
