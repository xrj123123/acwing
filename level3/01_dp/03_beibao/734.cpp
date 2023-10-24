// acwing 734 能量石
/*
    每块能量石有三个属性，s吃掉需要的时间，e最初的时间，l每秒失去的时间

    首先需要解决如何吃能量石，然后在判断吃那些
    假设第i块能量石si,ei,li, 第i+1块能量石si+1, ei+1, li+1
    如果先吃i，再吃i+1,获得的能力为：ei' + ei+1' - si * li+1, ei'和ei+1'表示吃第i块石头的时候i和i+1当前的能力
    如果先吃i+1,再吃i,获得的能量为：ei' + ei+1' - si+1 * li
    如果想要先吃i获得的能量多要保证：si * li+1 < si+1 * li, 即si/li < si+1/li+1
    因此可以先排序，然后按照01背包问题的思路求解
    f[i][j]表示前i块能量石，时间恰好为j时得到的最大能力值
    f[i][j] = max(f[i-1][j], f[i-1][j-s]+e-(j-s)*l);
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 10010;
int T;
int f[N];

struct Stone
{
    int s, e, l;
    bool operator< (const Stone& w)const
    {
        return s * w.l < l * w.s;
    }
}stone[N];

int main()
{   
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        int n, m = 0;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            int s, e, l;
            cin >> s >> e >> l;
            stone[i] = {s, e, l};
            m += s;
        }
        sort(stone, stone + n);

        memset(f, -0x3f, sizeof f);
        f[0] = 0;
        for (int i = 0; i < n; i++)
        {
            int s = stone[i].s, e = stone[i].e, l = stone[i].l;
            for (int j = m; j >= s; j--)
                f[j] = max(f[j], f[j - s] + e - (j - s) * l);
        }

        int res = 0;
        for (int i = 0; i <= m; i++)
            res = max(res, f[i]);
        printf("Case #%d: %d\n", t, res);
    }

    return 0;
}