// acwing 843 n皇后问题
#include <iostream>
using namespace std;
const int N = 20;
int n;
char g[N][N];
bool col[N], gd[N], ugd[N]; // col[i]表示第i列是否有皇后，gd[i]表示第i个正对角线是否有皇后,ugd[i]表示第i个反对角线是否有皇后

//   0 1 2
// 0 * * *     左上到右下的对角线,y=-x+b,b=y+x
// 1 * * *     右上到左下的对角线,y=x+b, b=y-x∈(-n,n),b=y-x+n
// 2 * * *

void dfs(int u) // 第u行
{
    if (u == n)
    {
        for (int i = 0; i < n; i++)
            printf("%s\n", g[i]);
        printf("\n");
        return;
    }

    for (int i = 0; i < n; i++) // 枚举第i列
    {
        if (!col[i] && !gd[u + i] && !ugd[n - u + i])
        {
            col[i] = gd[u + i] = ugd[n - u + i] = true;
            g[u][i] = 'Q';
            dfs(u + 1);
            col[i] = gd[u + i] = ugd[n - u + i] = false;
            g[u][i] = '.';
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g[i][j] = '.';

    dfs(0);
    return 0;
}
/*

// 第二种枚举方式,每行每列依次枚举
#include <iostream>
using namespace std;
const int N = 20;
int n;
char g[N][N];
bool row[N], col[N], gd[N], ugd[N]; // col[i]表示第i列是否有皇后，gd[i]表示第i个正对角线是否有皇后,ugd[i]表示第i个反对角线是否有皇后

void dfs(int x, int y, int s) // 第x行y列，放了s个皇后
{
    if (y == n)
        y = 0, x++;

    if (x == n)
    {
        if (s == n)
        {
            for (int i = 0; i < n; i++)
                puts(g[i]);
            puts("");
        }
        return;
    }

    // 不放皇后
    dfs(x, y + 1, s);

    //放皇后
    if (!row[x] && !col[y] && !gd[x + y] && !ugd[n - x + y])
    {
        row[x] = col[y] = gd[x + y] = ugd[n - x + y] = true;
        g[x][y] = 'Q';
        dfs(x, y + 1, s + 1);
        row[x] = col[y] = gd[x + y] = ugd[n - x + y] = false;
        g[x][y] = '.';
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g[i][j] = '.';

    dfs(0, 0, 0);
    return 0;
}
*/