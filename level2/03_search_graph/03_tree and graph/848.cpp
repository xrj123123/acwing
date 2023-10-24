// acwing 848 有向图的拓扑序列
// 若一个由图中所有点构成的序列 A 满足：对于图中的每条边 (x,y)，x 在 A 中都出现在 y 之前，则称 A 是该图的一个拓扑序列。
// 环没有拓扑序列,有向无环图一定存在拓扑序列,入度为0的点作为起点; 一个有向无环图至少存在一个入度为0的点

// 1.将所有入度为0的点入队  2.bfs  t=队头，枚举t的所有出边t->j,删掉t-j，d[j]--(j的入度-1)，if d[j]==0,j入队
// 如果是有向无环图，那么将入度为0的点作为起点，然后删除这个点和和其他点之间的关联，肯定又有一个入度为0的点(删除该点后还是拓扑序列)
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5 + 10;
int h[N], e[N], ne[N], idx;
int q[N], d[N]; // d[i]存储第i个点的入度
int n, m;

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool topsort()
{
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; i++) // 入度为0的点入队
        if (!d[i])
            q[++tt] = i;

    while (hh <= tt)
    {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            d[j]--; // 入度-1
            if (!d[j])
                q[++tt] = j;
        }
    }
    return tt == n - 1;
}

int main()
{
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        d[b] += 1;  // 入度+1
    }

    if (topsort())
    {
        for (int i = 0; i < n; i++)
            printf("%d ", q[i]);
        puts("");
    }
    else
        puts("-1");

    return 0;
}
