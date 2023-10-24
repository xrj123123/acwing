// acwing 292 炮兵阵地
/*
    棋盘式状态压缩dp
    摆放第i行时，会受到i-1和i-2行的影响，所以状态定义应多加一维
    状态表示：f[i][j][k]表示摆放了i行，且第i-1行状态为j，第i行状态为k时摆放炮台的最大值
    状态计算：f[i][a][b]是摆了i行，第i-1行状态为a，第i行状态为b
             f[i-1][c][a]是摆了i-1行，第i-2行状态为c，第i-1行状态为a
             f[i][a][b] = max(f[i][a][b], f[i-1][c][a] + cnt[b])

             合法方案: i行状态b，i-1行状态a，i-2行状态c
                      1. 每行1不能相邻或隔一个位置
                      2. ((a&b) | (a&c) | (b&c)) == 0
                      3. ((g[i-1]&a) | g[i]&b) == 0
*/
#include <iostream>
#include <vector>
using namespace std;

const int N = 110, M = 1 << 10;
vector<int> state;  // 合法状态
int cnt[M]; // 存放每个状态1的个数
int g[N];
int f[2][M][M]; 
int n, m;
/*
  利用滚动数组减小内存，如果第一位开100，内存占用会超
  每次将第一位&1，就可以奇偶交替，奇数偶数与1分别为1和0
*/

bool check(int state)
{
    for (int i = 0; i < m; i++)
        if ((state >> i & 1) && ((state >> i + 1 & 1) || (state >> i + 2 & 1)))
            return false;
    return true;
}

int count(int a)
{
    int cnt = 0;
    for (int i = 0; i < m; i++)
        if (a >> i & 1)
            cnt++;
    return cnt;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < m; j++)
        {
            char c;
            cin >> c;
            if (c == 'H')
                g[i] += 1 << j;
        }
    
    for (int i = 0; i < 1 << m; i++)
        if (check(i))
        {
            state.push_back(i);
            cnt[i] = count(i);
        }

    // 如果枚举到n，最后需要枚举f[n][i][j]求最大值，但是枚举到n+2，最后输出f[n+2][0][0]即可
    for (int i = 1; i <= n + 2; i++)
        for (int a : state) // i-1行状态
            for (int b : state) // i行状态
                for (int c :state)  // i-2行状态
                {
                    if (a & b || a & c || b & c) continue;
                    if (g[i - 1] & a || g[i] & b) continue;
                    f[i & 1][a][b] = max(f[i & 1][a][b], f[i - 1 & 1][c][a] + cnt[b]);
                }

    cout << f[n + 2 & 1][0][0] << endl;

    return 0;
}
