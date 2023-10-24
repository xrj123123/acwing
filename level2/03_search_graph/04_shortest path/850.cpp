// acwing 850 Dijkstra求最短路 II   堆优化版Dijkstra算法
/*
 朴素Dijkstra算法，找最近的点需要n次，更新边需要m次，所以总体是O(n^2)
 如果用堆优化，找最短的点是O(1),找n次; 更新边是O(logn),更新m次，时间复杂度为O(mlogn)
 不用手写堆，可以用优先队列实现,优先队列不能修改元素，因此需要修改元素就直接插入，因此会有冗余元素存在
 手写堆的话，在排序的时候还要交换下标
*/
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int, int> PII;
const int N = 1e6 + 10;
int n, m;
// 稀疏图，因此采用邻接表方式
int h[N], w[N], e[N], ne[N], idx; // w[i]为权重
int dist[N];
bool st[N];

void add(int a, int b, int c) // a->b 权值为c
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int Dijkstra()
{
    priority_queue<PII, vector<PII>, greater<PII>> heap; // 小根堆，存储的是{距离,下标}
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    heap.push({0, 1});

    while (heap.size())
    {
        auto t = heap.top(); // 头结点就是距离最小的节点
        heap.pop();

        int idx = t.second, distance = t.first;
        if (st[idx])
            continue; // 如果id这个点访问过了就不访问了

        st[idx] = true;

        for (int i = h[idx]; i != -1; i = ne[i]) // 用距离最小的节点，更新其他节点
        {
            int j = e[i];   // j是和i相连的点
            if (dist[j] > distance + w[i])
            {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    if (dist[n] == 0x3f3f3f3f)
        return -1;
    else
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

    int res = Dijkstra();
    printf("%d\n", res);
}
