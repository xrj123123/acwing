// acwing 1027 方格取数
/*
    只走一次f[i][j]表示从(1,1)走到(i,j)的路径最大值
    f[i][j] = max(f[i-1][j], f[i][j-1]) + w[i][j]

    走两次
    f[i1, j1, i2, j2]表示从(1,1)分别走到(i1, j1), (i2, j2)的路径最大值
    只有在i1+j1 == i2+j2时才会才重合

    用f[k, i1, i2]表示从(1,1)走到(i1, k-i1)和(i2, k-i2)的最大值，k = i1 + j1 = i2 + j2

    状态计算：
    f[k, i1, i2]的上一个状态
    1. 第一条向下，第二条向下   2. 第一条向下，第二条向右   3. 第一条向右，第二条向下   4. 第一条向右，第二条向右
    max(f[k-1][i1-1][i2-1]) + w[i1][j1](重合)
                            + w[i1][j1] + w[i2][j2](不重合)
*/
#include <iostream>
using namespace std;

const int N = 110;
int w[N][N], f[N * 2][N][N];
int n;

int main()
{
    scanf("%d", &n);

    int a, b, c;
    while (cin >> a >> b >> c, a || b || c)
        w[a][b] = c;

    for (int k = 2; k <= 2 * n; k++)
        for (int i1 = 1; i1 <= k; i1++)
            for (int i2 = 1; i2 <= k; i2++)
            {
                int j1 = k - i1, j2 = k - i2;
                int t = w[i1][j1];
                if (i1 != i2)   // 不重合的情况
                    t += w[i2][j2];
                int &x = f[k][i1][i2];
                x = max(x, f[k - 1][i1 - 1][i2 - 1] + t); 
                x = max(x, f[k - 1][i1 - 1][i2] + t);
                x = max(x, f[k - 1][i1][i2 - 1] + t);
                x = max(x, f[k - 1][i1][i2] + t);
            }

    cout << f[n * 2][n][n] << endl;

    return 0;
}