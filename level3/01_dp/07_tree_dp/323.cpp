// acwing 323 战略游戏
/*
    类似于没有上司的舞会
    没有上司的舞会：每条边最多选与一个节点，求最大值
    战略游戏：每条边至少选一个节点，求最小值
    这道题的输入方式可以确定它是一个有向图

    状态表示：f[i][j]表示以节点i为根节点，且i的状态为j的最小值。(j = 0, 1)
    状态计算：f[i][0] = min(f[k1][1] + f[k2][1] + ...)  (k1, k2...是i的子树)
             f[i][1] = min(min(f[k1][0], f[k1][1]) + min(f[k2][0], f[k2][1]) + ...)
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1510;
int h[N], e[N], ne[N], idx;
int st[N];
int f[N][2];
int n;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u)
{
    f[u][0] = 0;
    f[u][1] = 1;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        dfs(j);
        f[u][0] += f[j][1];
        f[u][1] += min(f[j][0], f[j][1]);
    }
}

int main()
{
    while (scanf("%d", &n) != -1) // scanf返回输入数据的个数，没有输入就返回-1
    {
        memset(st, 0, sizeof st);
        memset(h, -1, sizeof h);
        for (int i = 0; i < n; i++)
        {
            int id, cnt;
            scanf("%d:(%d) ", &id, &cnt);
            int son;
            while (cnt--)
            {
                scanf("%d", &son);
                add(id, son);
                st[son] = true;
            }
        }

        int root = 0;
        while (st[root]) root++;

        dfs(root);
        cout << min(f[root][0], f[root][1]);
    }

    return 0;
}