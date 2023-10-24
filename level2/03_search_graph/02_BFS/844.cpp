// acwing 844 走迷宫
#include <iostream>
#include <queue>
using namespace std;
typedef pair<int, int> PII;
const int N = 110;
int n, m;
int g[N][N], d[N][N]; // d[i][j]表示(i,j)离起点的距离
PII last[N][N];       // last[i][j]表示(i,j)前一个点
int fx[4] = {0, 0, 1, -1}, fy[4] = {1, -1, 0, 0};
queue<PII> q;

int bfs()
{
    q.push({0, 0});
    while (!q.empty())
    {
        auto t = q.front(); // 队头
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int tx = t.first + fx[i];
            int ty = t.second + fy[i];
            if (tx >= 0 && tx < n && ty >= 0 && ty < m && g[tx][ty] == 0 && d[tx][ty] == 0)
            {
                q.push({tx, ty});
                last[tx][ty] = t;
                d[tx][ty] = d[t.first][t.second] + 1;
            }
        }
    }

    // 输出路径
    int x = n - 1, y = m - 1;
    while (x || y)
    {
        cout << x << " " << y << endl;
        auto t = last[x][y];
        x = t.first, y = t.second;
    }

    return d[n - 1][m - 1];
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> g[i][j];

    cout << bfs() << endl;
}