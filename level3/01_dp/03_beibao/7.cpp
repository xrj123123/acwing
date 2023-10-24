// acwing 7 混合背包问题
/*
    01背包：f[i][j] = max(f[i-1][j], f[i-1][j-w]+v);
    完全背包：f[i][j] = max(f[i-1][j], f[i][j-v]+w);
    多重背包：f[i][j] = amx(f[i-1][j], f[i-1][j-v]+w, f[i-1][j-2v]+2w);
*/
#include <iostream>
using namespace std;

const int N = 1010;
int f[N];
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int v, w, s;
        cin >> v >> w >> s;
        if (s == 0) // 完全背包
            for (int j = v; j <= m; j++)
                f[j] = max(f[j], f[j - v] + w);
        else
        {
            if (s == -1)   // 01背包
                s = 1;
            for (int k = 1; k <= s; k *= 2)
            {
                for (int j = m; j >= k * v; j--)
                    f[j] = max(f[j], f[j - k * v] + k * w);
                s -= k;
            }
            if (s)
            {
                for (int j = m; j >= s * v; j--)
                    f[j] = max(f[j], f[j - s * v] + s * w);
            }
        }
    }

    cout << f[m] << endl;

    return 0;
}