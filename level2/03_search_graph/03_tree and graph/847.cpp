// acwing 847 图中点的层次
// 图: 1.有向图  2.无向图
// 有向图: 1.邻接矩阵 g[a][b]表示a->b的距离    2.邻接表(用的最多),开了n个单链表
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1e5 + 10;
queue<int> q;
int h[N], e[N], ne[N], idx;
int d[N];
int n, m;

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int bfs()
{
    q.push(1);
    memset(d, -1, sizeof d);
    d[1] = 0;

    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (d[j] == -1)
            {
                d[j] = d[t] + 1;
                q.push(j);
            }
        }
    }
    return d[n];
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    cout << bfs() << endl;

    return 0;
}
