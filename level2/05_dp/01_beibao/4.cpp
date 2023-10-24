// acwing 4 多重背包问题 I
/*
    f[i][j]=max(f[i-1][j-k*v[i]]+k*w[i])  k=0、1、2...s[i]

    f[i][j]=max(f[i-1][j],f[i-1][j-v]+w,f[i-1][j-2*v]+2*w,...,f[i-1][j-sv]+sw)
    f[i][j-v]=max(        f[i-1][j-v],  f[i-1][j-2*v]+w,...,  f[i-1][j-sv]+(s-1)w,f[i-1][j-(s+1)v]+sw)
    无法替换,因此无法用完全背包方式优化
*/
/* #include <iostream>
using namespace std;
const int N = 110;
int v[N], w[N], s[N];
int f[N][N];
int n, m;
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i] >> s[i];

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= s[i]; k++)
            {
                if (k * v[i] <= j)
                    f[i][j] = max(f[i][j], f[i - 1][j - k * v[i]] + k * w[i]);
            }
    cout<<f[n][m]<<endl;

    return 0;
} */

/*
    二进制优化:s=1023   0,1,2...1023
    1,2,4,8,16...512可以组合成1023中任意一个数
    将s分为logs个组，问题变为01背包问题，时间复杂度由O(NVs)变为O(NVlogs)
*/
#include <iostream>
using namespace std;
const int N = 12000; // N为物品个数*拆分个数,1000*log2000
int v[N], w[N];
int f[N];
int n, m;

int main()
{
    cin >> n >> m;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        int a, b, s;
        cin >> a >> b >> s;
        int k = 1;
        while (k < s)
        {
            cnt++;
            v[cnt] = k * a;
            w[cnt] = k * b;
            s -= k;
            k <<= 1;
        }
        if (s > 0)
        {
            cnt++;
            v[cnt] = s * a;
            w[cnt] = s * b;
        }
    }

    // 转为01背包问题
    for (int i = 1; i <= cnt; i++)
        for (int j = m; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);

    cout << f[m] << endl;

    return 0;
}