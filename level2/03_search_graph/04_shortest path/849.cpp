// acwing 849 Dijkstra求最短路 I

/*
最短路：1.单源最短路    n:点的数量  m:边的数量
            1.1 所有边权都是正数  (1)朴素Dijkstra算法 O(n^2)   (2)堆优化版的Dijkstra算法 O(mlogn)
            1.2 存在负权边       (1)Bellman-Fold  O(nm)  (让选择不超过k条边的时候使用)   (2)SPFA 一般O(m)，最坏O(nm)
        2.多源汇最短路  Floyd算法   O(n^3)
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 510;
int n, m;
int g[N][N], dist[N]; // dist[i]表示第i个点到起点的距离
bool st[N];

int Dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    for (int i = 0; i < n; i++)
    {
        int t = -1; // 找出离起点最近的点，且没有确定过最短距离
        for (int j = 1; j <= n; j++)
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;
        st[t] = true;

        for (int j = 1; j <= n; j++)    // 通过点t更新其他点到起点的距离
            dist[j] = min(dist[j], dist[t] + g[t][j]);
    }
    if (dist[n] == 0x3f3f3f3f)
        return -1;
    else
        return dist[n];
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(g, 0x3f, sizeof g);

    while (m--)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        g[x][y] = min(g[x][y], z);
    }

    int res = Dijkstra();
    printf("%d\n", res);

    return 0;
}