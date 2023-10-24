// acwing 12 背包问题求具体方案
/*
    01背包问题：f[i][j] = max(f[i-1][j], f[i-1][j-v]+w);
    最终结果为：f[n][m]

    要求具体方案即求如何转移到f[n][m]，从第n-1个判断，
    判断f[n][m]等于f[n-1][m]还是等于f[n-1][m-v]+w,等于哪个就是从哪个转移而来,依次往前推
    而题目要求字典序最小，因此要从前往后判断，
    在第一个物品时，有三个选择：1.必须选(选) 2.必须不选(不选) 3.可选可不选(选)
    此时将外层循环枚举物品的顺序逆序即可
*/
#include <iostream>
using namespace std;

const int N = 1010;
int f[N][N];
int v[N], w[N];
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)    
        cin >> v[i] >> w[i];
    
    for (int i = n; i >= 1; i--)    // 从大到小枚举,这样枚举到最后就是1号了
        for (int j = 0; j <= m; j++)
        {
            f[i][j] = f[i + 1][j];
            if (j >= v[i])
                f[i][j] = max(f[i][j], f[i + 1][j - v[i]] + w[i]);
        }

    // 枚举路径, 此时f[1][m]是最大值
    int j = m;
    for (int i = 1; i <= n; i++)
    {
        if (j >= v[i] && f[i][j] == f[i + 1][j - v[i]] + w[i])   // 可以选那就必选
        {
            cout << i << " ";
            j -= v[i];
        }
    }
    cout << endl;
    return 0;
}