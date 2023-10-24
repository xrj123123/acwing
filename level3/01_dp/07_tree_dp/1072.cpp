// acwing 1072 树的最长路径
/*
    树的最长路径就是树的直径，一般有两种方法求树的直径
    1.两次DFS或BFS，第一次任取一个点找到离其最远的一个点(直径的某个端点),然后以该点为起点，找到离其最远的点，两点距离即为树的直径
      如果边权为负，无法使用
    2.树形dp，通过集合的思想求直径，边权可正可负
      遍历所有的点，求经过当前点的最长路径，可以把当前点看为一个挂钩；如果他只有一边，求他可以到达的最远距离；如果他有两边，
      左边和右边都挂一棵树，就求和他相连节点距离最大值d1与次大值d2，d1+d2+和当前点的距离即为经过当前点的最长路径
      如果当前遍历到的点和他子节点距离为负，那么就可以不选他，因为是无向树，为了防止死循环，即父节点遍历到子节点，子节点又遍历
      父节点。我们将父节点作为参数传进去，当该点子节点是父节点时continue
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5 + 10, M = 2* N;
int h[N], e[M], ne[M], w[M], idx;
int n, res;

void add(int a, int b, int c)
{
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx++;
}

int dfs(int u, int father)
{
    int d1 = 0, d2 = 0;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (j == father) continue;
        int d = dfs(j, u) + w[i];
        if (d > d1)
            d2 = d1, d1 = d;
        else if (d > d2)
            d2 = d;
    }
    res = max(res, d1 + d2);
    return d1;
}

int main()
{
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    dfs(1, -1);
    cout << res << endl;

    return 0;
}