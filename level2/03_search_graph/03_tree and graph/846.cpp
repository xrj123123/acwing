// acwing 846 树的重心
// 树是一种特殊的无环连通图
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5 + 10, M = N * 2;
int h[N], e[M], ne[M], idx;
bool st[N];
int ans = N;
int n;

void add(int a, int b) // a->b有通路
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 以u为根的子树中点的数量
int dfs(int u)
{
    st[u] = true; // 标记一下被搜过了

    int sum = 1, res = 0; // sum记录以u为根节点的所有节点数量，res存子树中最大数量
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            int s = dfs(j);
            res = max(res, s);
            sum += s;
        }
    }
    res = max(res, n - sum);
    ans = min(ans, res);
    return sum;
}

int main()
{
    memset(h, -1, sizeof h);
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }

    dfs(1);
    printf("%d\n", ans);

    return 0;
}
