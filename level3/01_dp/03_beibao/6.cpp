// acwing 6 多重背包3
/*
    单调队列优化
    f[i][j]表示前i个物品容量为为j的最大价值
    f[i][j] = max(f[i-1][j], f[i-1][j-v]+w, f[i-1][j-2v]+2w, ... f[i-1][j-sv]+sw)
    f[i][j-v] = max(         f[i-1][j-v],   f[i-1][j-2v]+w,  ... f[i-1][j-sv]+(s-1)w, f[i-1][j-(s+1)v]+sw)
    f[i][j-2w] = max(                       f[i-1][j-2v],    ... f[i-1][j-sv]+(s-2)w, f[i-1][j-(s+1)v]+(s-1)w, f[i-1][j-(s+2)v]+sw)
    ...
    f[i][r+2v] = max(f[i-1][r+2v], f[i-1][r+v] + w, f[i-1][r] + 2w)
    f[i][r+v]  = max(              f[i-1][r+v],     f[i-1][r] + w)
    f[i][r]    = max(                               f[i-1][r])
    (0 <= r < m)

    每个物品可以选0、1、2...s个
    背包的容量为m，因此将体积从m-0依次枚举即可得到最优解
    f[0]   f[v]   f[2v]   ...    f[sv]
    f[1]   f[v+1] f[2v+1]        f[sv+1]
    f[2]   f[v+2] f[2v+2]        f[sv+2]
    ... 
    f[r]   f[v+r] f[2v+r]        f[sv+r]
    (0 <= r < m)
    m == sv+r
    因此可以将f数组分类r类，每一类的值都是在同类之间转化得到
    即: f[sv+r]只依赖于f[r], f[v+r], f[2v+r] ... f[sv+r]
    因此可以维护一个单调队列来得到结果，这样，就变成了维护r个单调队列的问题

    f[r]        = f[r]
    f[v+r]      = max(f[v+r],  f[r]+w)
    f[2v+r]     = max(f[2v+r], f[v+r]+w, f[r]+2w)
    ...
    f[sv+r]     = max(f[sv+r],     f[(s-1)v+r]+w, f[(s-w)v+r]+2w ... f[r]+sw)      (共s+1项，此时队列满，开始滑动)
    f[(s+1)v+r] = max(f[(s+1)v+r], f[sv+r]+w,     f[(s-1)v+r]+2w ... f[v+r]+sw)    (共s+1项，此时队列满，开始滑动)
    f[(s+2)v+r] = max(f[(s+2)v+r], f[(s+1)v+r]+w, f[sv+r]+2w     ... f[s+v+r]+sw)  (共s+1项，此时队列满，开始滑动)

    转化一下
    f[r]        = f[r]
    f[v+r]      = max(f[r], f[v+r]-w) + w
    f[2v+r]     = max(f[r], f[v+r]-w, f[2v+r]-2w) + 2w
    f[3v+r]     = max(f[r], f[v+r]-w, f[2v+r]-2w, f[3v+r]-3w) + 3w
    ...
    每次入队的值为f[sv+r]-sv

    单调队列问题：
    1.维护队列中的元素，最多s+1个
    2.维护队列的单调性，保持队列是单调下降的，如果队尾元素<=要入队的元素，那么队尾出队

    时间复杂度  O(n*v*(m/v)) = O(nm)
*/
#include <iostream>
#include <cstring>
using namespace std;

const int N = 20010;
int f[N], g[N]; // g数组用于存放上一轮的f，即f[i-1][j]
int q[N];
int n, m;

int main()
{
    cin >> n >> m;
    int v, w, s;
    for (int i = 0; i < n; i++)
    {
        cin >> v >> w >> s;
        memcpy(g, f, sizeof f);
        for (int r = 0; r < v; r++) // 余数
        {
            int hh = 0, tt = -1;
            for (int j = r; j <= m; j += v)  // 每一组单调队列
            {
                if (hh <= tt && (j - q[hh]) / v > s)  
                    hh++;
                while (hh <= tt && g[q[tt]] - (q[tt] - r) / v * w <= g[j] - (j - r) / v * w)
                    tt--;
                q[++tt] = j;
                if (hh <= tt)
                    f[j] = max(f[j], g[q[hh]] + (j - q[hh]) / v * w);
            }
        }
    }

    cout << f[m] << endl;

    return 0;
}