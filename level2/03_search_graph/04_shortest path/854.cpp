// acwing 854 Floyd求最短路
/*
    状态表示: f[k, i, j]表示从i到j,中间点只经过1到k(不包括i和j)的所有路径最小值
    状态计算: f[k, i, j] = min(f[k-1, i, j], f[k-1, i, k] + f[k-1, k, j])  
              f[k-1, i, j]表示不经过第k个点
              f[k-1, i, k] + f[k-1, k, j]表示经过第k个点
              可以发现f[k, i, j]只和k-1层有关系，所有第一维可以去掉
              f[i][j] = min(f[i][j], f[i][k] + f[k][j])
              f[i][j]一定是属于第k-1层的，而f[i][k]不一定属于k-1层，如果k小于j，那么f[i][k]属于第k层,即f[k, i, k] + f[k-1, k, j]
              如果有负环，则一定不存在最短路，但是存在最短路，说明从i到j一定存在一条路径不包括重复点且最短
              所以f[k,i,k]表示从i走到k，将1到k作为中间点，如果将k作为中间点，即k到k为一个环，更新最短路时会去掉这个环，所以此时答案不会被影响
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 210;
int n, m, k;
int d[N][N];

void Floyd()
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i == j)
                d[i][j] = 0;
            else
                d[i][j] = 0x3f3f3f3f;
    while (m--)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        d[x][y] = min(d[x][y], z);
    }

    Floyd();

    while (k--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (d[x][y] > 0x3f3f3f3f / 2)
            puts("impossible");
        else
            printf("%d\n", d[x][y]);
    }

    return 0;
}