// acwing 842 排列数字
#include <iostream>
using namespace std;
const int N = 10;
int path[N];
bool st[N];
int n;

void dfs(int u)
{
    if (u == n) // 到最后一位数字，输出
    {
        for (int i = 0; i < n; i++)
            printf("%d ", path[i]);
        printf("\n");
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (!st[i])
        {
            st[i] = true;
            path[u] = i;
            dfs(u + 1);
            st[i] = false;
        }
    }
}

int main()
{
    scanf("%d", &n);
    dfs(0);

    return 0;
}