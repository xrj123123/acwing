// acwing 901 滑雪
/*
    状态表示：
        dp[i][j]表示从i行j列开始滑的最大长度
    状态计算：
        dp[i][j] = max(dp[i][j+1], dp[i][j-1], dp[i-1][j], dp[i+1][j]) + 1
 */
#include <iostream>
#include <cstring>
using namespace std;

const int N = 310;
int n, m;
int a[N][N];
int f[N][N];

int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

int dp(int x, int y)
{
    int &v = f[x][y];
    if (v != -1)    // 如果计算过了就直接返回
        return v;

    v = 1;
    for (int i = 0; i < 4; i++)
    {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (tx >= 0 && tx < n && ty >= 0 && ty < m && a[tx][ty] < a[x][y])
            v = max(v, dp(tx, ty) + 1);
    }
    return v;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &a[i][j]);

    memset(f, -1, sizeof f);    // f[i][j]=-1 表示未计算过

    int res = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            res = max(res, dp(i, j));

    printf("%d\n", res);

    return 0;
}