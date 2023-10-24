// acwing 1074 二叉苹果数
/*
    这道题本质就是有依赖的背包问题，树枝上苹果的数量就是权值
    状态表示：f[i][j]表示以i为根节点，选j条边的最大值
    状态计算：当前节点i的每个子树看成一个分组，求的是选哪几个分组
             如果选第k个子树，那么最多给第k个子树分j-1条边，因为k和i之间还有一条边
             f[i][j] = max(f[i][j], f[i][j-k-1]+f[son][k]+w[i]);
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 110, M = N * 2;
int h[N], e[M], w[M], ne[M], idx;
int f[N][N];
int n, m;

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void dfs(int u, int father)
{
    for (int i = h[u]; i != -1; i = ne[i])  // 枚举物品
    {
        int son = e[i];
        if (son == father) continue;
        dfs(son, u);
        for (int j = m; j >= 0; j--)    // 枚举体积
            for (int k = 0; k < j; k++) // 枚举子树占用的体积
               f[u][j] = max(f[u][j], f[u][j - k - 1] + f[son][k] + w[i]);
    }
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }

    dfs(1, -1);

    cout << f[1][m] << endl;
    return 0;
}