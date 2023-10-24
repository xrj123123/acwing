// acwing 859 Kruskal算法求最小生成树
/*
 1. 先将所有边按权重从回小到大排序 O(mlogm)
 2. 枚举每条边a,b,权重为c       O(m)
     if a,b不连通
        将这条边加入到集合
*/
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200010;
int p[N];
int n, m;

struct node
{
    int a, b, w;
    bool operator<(const node W) const
    {
        return w < W.w;
    }
} edges[N];

int find(int x)
{
    if (x != p[x])
        p[x] = find(p[x]);
    return p[x];
}

void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
        p[fx] = fy;
}

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++)
        p[i] = i;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edges[i] = {u, v, w};
    }
    sort(edges, edges + m);

    int res = 0, cnt = 0;
    for (int i = 0; i < m; i++)
    {
        int x = edges[i].a, y = edges[i].b, z = edges[i].w;
        if (find(x) != find(y))
        {
            merge(x, y);
            res += z;
            cnt++;
        }
    }

    if (cnt < n - 1)
        puts("impossible");
    else
        printf("%d\n", res);

    return 0;
}
