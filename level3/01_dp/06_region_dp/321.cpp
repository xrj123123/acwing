// acwing 321 棋盘分割
/*
    区间dp + 记忆化搜索 + 前缀和
    状态表示：集合：f[x1,y1,x2,y2,k]表示将左上角为(x1,y1)，左下角为(x2,y2)的矩阵分为k个矩阵的方案
             属性：方差最小
    状态计算：对于每一个f[x1,y1,x2,y2,k]可以将他横切一刀，可以选上边部分，也可以选下边部分；可以将他竖切一刀，可以选左或右
*/
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 15, M = 9;
const double INF = 1e9;
double f[M][M][M][M][N];
int s[M][M];    // 前缀和
double X;   // 均值
int n, m = 8;

double get(int x1, int y1, int x2, int y2)
{
    double sum = s[x2][y2] - s[x2][y1 - 1] - s[x1- 1][y2] + s[x1 - 1][y1 - 1] - X;
    return (double)sum * sum / n;
}

double dp(int x1, int y1, int x2, int y2, int k)
{
    double &v = f[x1][y1][x2][y2][k];
    if (v >= 0) return v;
    if (k == 1) return v = get(x1, y1, x2, y2);

    v = INF;
    // 横着切
    for (int i = x1; i < x2; i++)
    {
        // 保留下边
        v = min(v, get(x1, y1, i, y2) + dp(i + 1, y1, x2, y2, k - 1));
        // 保留上边
        v = min(v, get(i + 1, y1, x2, y2) + dp(x1, y1, i, y2, k - 1));
    }
    
    // 竖着切
    for (int i = y1; i < y2; i++)
    {
        // 保留左边
        v = min(v, get(x1, i + 1, x2, y2) + dp(x1, y1, x2, i, k - 1));
        // 保留右边
        v = min(v, get(x1, y1, x2, i) + dp(x1, i + 1, x2, y2, k - 1));
    }
    return v;
}

int main()
{   
    cin >> n;
    memset(f, -1, sizeof f);    // double类型初始化-1，每个值都是nan
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
        {
            cin >> s[i][j];
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    X = (double)s[m][m] / n;
    
    printf("%.3f\n", sqrt(dp(1, 1, m, m, n)));

}
