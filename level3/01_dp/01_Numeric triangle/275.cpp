// acwing 275 传纸条
/*
    和1027方格取数一样  
    注意:  1 <= i1 <= n;  i <= k - i1 <= m
    max(1, k - m) <= i1 <= min(n, k - 1)
    (1 - k 也可以)
*/
#include <iostream>
using namespace std;

const int N = 55;
int a[N][N], f[2 * N][N][N];
int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);

    for (int k = 2; k <= n + m; k++)
        for (int i1 = max(k - m, 1); i1 <= min(n, k - 1); i1++)
            for (int i2 = max(k - m, 1); i2 <= min(n, k - 1); i2++)
            {
                int j1 = k - i1, j2 = k - i2;
                int t = a[i1][j1];
                if (i1 != i2)
                    t += a[i2][j2];
                int &x = f[k][i1][i2];
                x = max(x, f[k - 1][i1][i2] + t);
                x = max(x, f[k - 1][i1 - 1][i2] + t);
                x = max(x, f[k - 1][i1][i2 - 1] + t);
                x = max(x, f[k - 1][i1 - 1][i2 - 1] + t);
            }

    cout << f[n + m][n][n] << endl;
    return 0;
}