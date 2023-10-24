// acwing 1020 潜水员
/*
    f[i][j][k]表示前i个物品，花费一恰大于等于j，花费二大于等于k的最小花费
    最终求解结果为f[N][m][n]

    注意: 如果f[0][j][k]表示选0件物品，第一维不超过j，第二位不超过k，则f[0][j][k]是合法的，初始化为0
          如果f[0][j][k]表示选0件物品，第一维等于j，第二维等于k，则f[0][0][0] = 0，其余都不合法，初始化为+oo
          如果f[0][j][k]表示选0件物品，第一维至少为j，第二维至少为k，则f[0][0][0] = 0，其余都不合法，初始化为+oo

          体积最多为j，f全置位0，v ≥ 0
          体积恰好为j，f[0] = 0, 其余为+oo，v ≥ 0
          体积最多为j，f[0] = 0, 其余为+oo，v无限制
*/
#include <iostream>
#include <cstring>
using namespace std;

const int N = 22, M = 80;
int f[N][M];
int m, n, t;

int main()
{
    cin >> m >> n;
    cin >> t;
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    for (int i = 0; i < t; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        for (int j = m; j >= 0; j--)
            for (int k = n; k >= 0; k--)
                // 这里j-a和k-b为负数也是合法的，因为f[i][j]是求至少是i和j，负数的情况和0一样，因此赋值为0    
                f[j][k] = min(f[j][k], f[max(0, j - a)][max(0, k - b)] + c);
    }

    cout << f[m][n] << endl;

    return 0;
}
