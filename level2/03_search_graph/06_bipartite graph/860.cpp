// acwing 860 染色图判定二分图
/*
二分图
    1. 染色法 O(n+m)
        用来判断一个图是不是二分图(两个集合，内部没有边)
        一个图是二分图，当且仅当图中不含奇数环; 一个图不含奇数环，一定是二分图
    2. 匈牙利算法 O(mn),实际运行时间一般小于O(mn)   给一个二分图，求最大匹配
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 100010, M = 200010;
int h[N], e[M], ne[M], idx;
int color[N];
int n, m;

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 将第u个点染色为c
bool dfs(int u, int c)
{
    color[u] = c;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!color[j])
        {
            if (!dfs(j, 3 - c)) // 如果当前点没有染色，那么就将其染色，如果出现矛盾就返回false
                return false;
        }
        else // 当前点染色的话，判断是否冲突
            if (color[j] == c)
                return false;
    }
    return true;
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    while (m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }

    bool flag = true;
    for (int i = 1; i <= n; i++)
    {
        if (!color[i])
        {
            if (!dfs(i, 1))
            {
                flag = false;
                break;
            }
        }
    }
    if (flag)
        puts("Yes");
    else
        puts("No");

    return 0;
}