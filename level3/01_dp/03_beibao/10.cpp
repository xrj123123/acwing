// acwing 10 有依赖的背包问题
/*
    该问题是如果选择物品i，那么i的父节点也必须选，构成一个树形结构
    按背包问题的状态转移来看，当前状态只依赖于i-1的状态，那么对于节点i，需要枚举他的子节点2^k种状态，
    时间复杂度最坏达到O(N * 2^N * V)
    因此需要换一种方式
    f[i][j]
    状态表示：集合：第i件物品作为根节点，且选上i，体积不超过j的情况
             属性：Max
    状态计算：不选第i件物品：0
             选第i件物品：考虑子物品且总体积不超过0     max{f(soni,0) + wi}   f(soni,j)表示i的所有子节点共用体积j的最大值)
             选第i件物品：考虑子物品且总体积不超过1     max{f(soni,1) + wi}
             ...
             选第i件物品：考虑子物品且总体积不超过j-vi  max{f(soni,j-vi) + wi}

             相当于是一个分组背包问题，在节点i处，他的子节点看选哪几个
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 110;
int f[N][N];
int h[N], e[N], ne[N], idx;
int v[N], w[N];
int n, m;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u)
{
    // 枚举所有u节点的子节点
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int son = e[i];
        dfs(son);   // 先计算出子节点的花费
        for (int j = m - v[u]; j >= 0; j--) // 选节点u，所有j从m-v[u]开始
            for (int k = 0; k <= j; k++)    // 枚举子节点占用k体积时的最大值
                f[u][j] = max(f[u][j], f[u][j - k] + f[son][k]);
    }

    // 加上当前w[u]
    for (int j = m; j >= v[u]; j--)
        f[u][j] = f[u][j - v[u]] + w[u];
    for (int j = 0; j < v[u]; j++)  // 体积小于v[u]，则选不了u，赋为0
        f[u][j] = 0;
}

int main()
{
    cin >> n >> m;
    int root = 0;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++)
    {
        int p;
        cin >> v[i] >> w[i] >> p;
        if (p == -1)
            root = i;
        else
            add(p, i);
    }

    dfs(root);

    cout << f[root][m] << endl;

    return 0;
}