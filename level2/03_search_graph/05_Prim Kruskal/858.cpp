// acwing 858 Prim算法求最小生成树
/*
最小生成树：
 稠密图一般使用朴素Prim算法，稠密图使用Kruskal
 Prim: 1. 朴素版(稠密图) O(n^2)  2. 堆优化版(稀疏图) O(mlogn)
 Kruskal: O(mlogm)
 */
#include <iostream>
#include <cstring>
using namespace std;
const int N = 510, inf = 0x3f3f3f3f;
int g[N][N], dist[N], st[N];
int n, m;

int Prim()
{
    int res = 0;
    memset(dist, 0x3f, sizeof dist);
    for (int i = 0; i < n; i++) // 每次加入一个点，总共加入n个点
    {
        // 先找到离集合最近的点
        int t = -1;
        for (int j = 1; j <= n; j++)
        {
            if (!st[j] && (t == -1 || dist[j] < dist[t]))
                t = j;
        }
        st[t] = true;

        if (i && dist[t] == inf) // 如果当前最近的点无法到达，即dist[t]==inf，直接返回
            return inf;

        // 如果不是第1个点，res就加上，这里必须先加dist[t]，因为如果出现负环，且是自环，那么更新时会把自己更新掉
        if (i)
            res += dist[t];

        // 用最近的点去更新其他点到集合的距离
        for (int j = 1; j <= n; j++)
            dist[j] = min(dist[j], g[t][j]);
    }
    return res;
}

int main()
{
    memset(g,0x3f,sizeof g);
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u][v] = g[v][u] = min(g[u][v], w);
    }

    int res = Prim();
    if (res == inf)
        puts("impossible");
    else
        printf("%d\n", res);
}