// acwing 1068 环形石子合并
/*
    环形转为链型
    将n堆石子合并成一堆，且这n堆围成一个环，可以枚举n个缺口，对每个缺口进行一次区间dp，然后求最小值，O(n^4)超时
    假设n堆石子编号为1 2 3 4 5 6 7 8，可以用2n堆，1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8，然后当缺口在1-8之间时，就是求f[1,8]
    缺口在1-2之间，就是求f[2,1]，最后枚举长度为n的区间，求出最小值，O((2n)^3)
*/
#include <iostream>
#include <cstring>
using namespace std;
#define INF 0x3f3f3f3f
const int N = 410;
int a[N], s[N];
int f[N][N], g[N][N]; 
int n;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i = 1; i <= 2 * n; i++)
        s[i] = s[i - 1] + a[i];
    
    memset(f, 0x3f, sizeof f);
    memset(g, -0x3f, sizeof g);

    for (int len = 1; len <= n; len++)
        for (int l = 1; l + len - 1 <= 2 * n; l++)
        {
            int r = l + len - 1;
            if (len == 1)
            {
                f[l][r] = 0;
                g[l][r] = 0;
            }
            for (int k = l; k < r; k++)
            {
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
                g[l][r] = max(g[l][r], g[l][k] + g[k + 1][r] + s[r] - s[l - 1]);
            }
        }

    int minv = INF, maxv = -INF;
    for (int i = 1; i <= n; i++)
    {
        minv = min(minv, f[i][i + n - 1]);
        maxv = max(maxv, g[i][i + n - 1]);
    }
    cout << minv << endl << maxv << endl;

    return 0;
}