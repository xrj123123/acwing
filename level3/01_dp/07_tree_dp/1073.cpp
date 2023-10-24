// acwing 1073 树的中心
/*
    树形dp
    求出每个点到其他点的最长距离，在求其中最短的即可
    如果像1072树的最长路径那样，枚举每个点作为根节点，然后dfs一遍，时间复杂度O(n^2)超时
    但树形dp，向下一次dfs，向上一次dfs，时间复杂度为O(2n)
    d1[u]表示u节点向下走最长路径
    d2[u]表示u节点向下走次长路径
    p1[u]表示u节点向下走的最长路径走到哪个点
    p2[u]表示u节点向下走的次长路径走到哪个点
    up[u]表示u节点向上走的最长路径
    向下走就直接dfs
    向上走的话，相同的地方就是从u节点走向他的父节点，不同的就是从父节点走向其他节点，父节点可以向上走，也可以向下走
    因此向上走的最远距离就是求u的父节点不经过u的最远距离
    如果父节点向下走的最远距离不经过u，那么父节点到其他点的最远距离就是max(d1,up)，如果经过u，那么最远距离就是max(d2,up)
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e4 + 10, M = N * 2, INF = 0x3f3f3f3f;
int h[N], e[M], ne[M], w[M], idx;
int d1[N], d2[N], p1[N], p2[N], up[N];
int n;

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

// 向下dfs
int dfs_d(int u, int father)
{
    d1[u] = d2[u] = -INF;   // 权值都为正数，因此这里初始化为0就可以
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (j == father) continue;
        int d = dfs_d(j, u) + w[i];
        if (d > d1[u])
        {
            d2[u] = d1[u], p2[u] = p1[u];
            d1[u] = d, p1[u] = j;
        }else if (d > d2[u])
        {
            d2[u] = d;
            p2[u] = j;
        }
    }
    if (d1[u] == -INF) d1[u] = d2[u] = 0;   // 处理叶子结点
    return d1[u];
}

// 向上dfs
void dfs_u(int u, int father)
{
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (j == father) continue;
        if (p1[u] == j) up[j] = w[i] + max(up[u], d2[u]);  // 父节点向下的最长距离经过j
        else up[j] = w[i] + max(up[u], d1[u]); // 父节点向下的最长距离不经过j
        dfs_u(j, u);
    }
}

int main()
{
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    dfs_d(1, -1);
    dfs_u(1, -1);

    int res = INF;
    for (int i = 1; i <= n; i++)
        res = min(res, max(d1[i], up[i]));

    cout << res << endl;

    return 0;
}