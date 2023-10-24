// acwing 285 没有上司的舞会
/*
    状态表示：
        f[u][0] 表示从以u为根节点的子树中选，不选u这个点的方案
        f[u][1] 表示从以u为根节点的子树中选，选u这个点的方案
        求max
    状态计算：
        假设当前节点为u，u的儿子为s1、s2，那么f[u][0] = max(f[s1][0], f[s1][1]) + max(f[s2][0], f[s2])
                                           f[u][1] = f[s1][0] + f[s2][0] + w[u]
 */
#include <iostream>
#include <cstring>
using namespace std;
const int N = 6010;

int happy[N];
int f[N][2];
int h[N], e[N], ne[N], idx;
bool has_father[N];
int n;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u)
{
    f[u][1] = happy[u];
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        dfs(j);
        f[u][1] += f[j][0];
        f[u][0] += max(f[j][0], f[j][1]);
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> happy[i];

    memset(h, -1, sizeof h); 
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        has_father[a] = true;
        add(b, a);
    }

    // 求根节点
    int root = 1;
    while (has_father[root])
        root++;

    dfs(root);

    int res = max(f[root][0], f[root][1]);
    cout << res << endl;

    return 0;
}