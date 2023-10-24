// acwing 487 金明的预算方案
/*
    每个主件，可以配0、1、2个配件，最多可分为四类
    即将每个主件分为一组，每个组最多选一个，然后求最大值

    分组背包问题
*/
#include <iostream>
#include <vector>
using namespace std;

#define v first
#define w second
typedef pair<int, int> PII;

const int N = 70, M = 32010;
PII master[N];  // master[i]存编号为i的主键的价格和重要度
vector<PII> resent[N];  // resent[i]表示主件i的附件
int f[M];
int n, m;

int main()
{
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
    {
        int v, w, q;
        cin >> v >> w >> q;
        if (!q)
            master[i] = {v, v * w};
        else
            resent[q].push_back({v, v * w});
    }

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--)
            for (int k = 0; k < 1 << resent[i].size(); k++) // x个附件，2^x种选法
            {
                int v = master[i].v, w = master[i].w;
                for (int u = 0; u < resent[i].size(); u++)
                {
                    if (k >> u && 1)   
                    {
                        v += resent[i][u].v;
                        w += resent[i][u].w;
                    }
                }
                if (j >= v)
                    f[j] = max(f[j], f[j - v] + w);
            }

    cout << f[m] << endl;

    return 0;
}
