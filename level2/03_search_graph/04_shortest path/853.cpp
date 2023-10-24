// acwing 853 有边数限制的最短路
/*
1.for n 次 ; 迭代k次表示：从1号点经过了不超过k条边到其他点的距离；如果第n次更新时，
    dist还发生变化(经过了n条边，有n+1个点，则一定有两个点一样)，说明存在负权边的环
2. for 所有边 a->b--w   dist[b]=min(dist[b],dist[a]+w)
*/

#include <iostream>
#include <cstring>
using namespace std;
const int N = 510, M = 10010;
int n, m, k;
int dist[N], last[N]; // last数组存的是dist上一次更新的备份,假设1->2=1,2->3=1，初始dist[2]=+00,
                      // 第一次更新dist[2]=1,更新dist[3]时，就用dist[2]来更新了，所以应该用上一次的结果更新
struct node
{
    int a, b, c;
} edges[M];

int bellman_ford()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    for (int i = 0; i < k; i++) // 不超过k条边，所以循环k次
    {
        memcpy(last, dist, sizeof dist);

        for (int j = 0; j < m; j++)
        {
            int x = edges[j].a, y = edges[j].b, w = edges[j].c;
            dist[y] = min(dist[y], last[x] + w);
        }
    }

    return dist[n];
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        edges[i] = {x, y, z};
    }

    int t = bellman_ford();
    if (t > 0x3f3f3f3f / 2)
        puts("impossible");
    else
        printf("%d\n", t);

    return 0;
}
