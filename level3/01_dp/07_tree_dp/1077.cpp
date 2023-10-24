// acwing 1077 皇宫看守
/*
    和战略游戏不同点在于，战略游戏是看守边，因此每条边至少有一个点要被选
    而皇宫看守是看守点，每个点要么被自己看守，看么被父节点看守，要么被子节点看守。因此就有了三种状态
    状态表示：f[i][0]表示第i个点被父节点看到，f[i][1]表示第i个点被子节点看到，f[i][2]表示第i个点被自己看到
    状态计算：f[i][0] = ∑ min(f[j][1], f[j][2]);    j是i的子节点
             f[i][2] = ∑ min(f[j][0], f[j][1], f[j][2]) + w[i];
             f[i][1] = min(f[k][2] + ∑(j!=k)min(f[j][1], f[j][2]))
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1510, INF = 0x3f3f3f3f;
int h[N], e[N], w[N], ne[N], idx;
int f[N][3];
int st[N];
int n;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u)
{   
    f[u][0] = 0;
    f[u][1] = INF;
    f[u][2] = w[u];
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        dfs(j);
        f[u][0] += min(f[j][1], f[j][2]);
        f[u][2] += min(min(f[j][0], f[j][1]), f[j][2]);
    }
    
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        // u节点被子节点j看到，因此要加一个f[j][2]，然后加上不包括j的其他节点的最小值
        // f[u][0]在上边计算过u所有子节点的最小值之和，因此减去被自己看到的这个节点就行
        f[u][1] = min(f[u][1], f[j][2] + f[u][0] - min(f[j][1], f[j][2]));
    }
}

int main()
{
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n; i++)
    {
        int id, cost, cnt;
        cin >> id >> cost >> cnt;
        w[id] = cost;
        while (cnt--)
        {
            int son;
            cin >> son;
            add(id, son);
            st[son] = true;
        }
    }

    int root = 1;
    while (st[root]) root++;

    dfs(root);

    cout << min(f[root][1], f[root][2]) << endl;

    return 0;
}