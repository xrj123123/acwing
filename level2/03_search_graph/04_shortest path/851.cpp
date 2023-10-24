// acwing 851 spfa求最短路
/*
    spfa是对bellman-Fold进行优化，bellman-Fold每次对所有边进行迭代，
    dist[y] = min(dist[y], last[x] + w);   
    如果last[x]没有变化，那么dist[y]也不需要更新
    因此每次只需要将变化过的点放入队列，每次从队列取来更新后边的点即可

    这里的st数组标记的是该点是否在队列中
*/
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1e5 + 10;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
bool st[N];
int n, m;

void add(int a, int b, int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int spfa()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    st[1] = true; // st[i]表示第i个点是否在队列中

    while (q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false; // 从队列取出后变为false

        for (int i = h[t]; i != -1; i = ne[i]) // 更新和t相连的节点
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])
                {
                    q.push(j); // 距离改变的点再加入队列
                    st[j] = true;
                }
            }
        }
    }

    return dist[n];
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    while (m--)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
    }

    int t = spfa();
    if (t > 0x3f3f3f3f / 2)
        puts("impossible");
    else
        printf("%d\n", t);

    return 0;
}