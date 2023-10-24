// acwing 327 玉米地
/*
    棋盘式的状态压缩dp
    小国王相当于放置3×3的方格，玉米田相当于放置一个十字形的方格
    状态表示：f[i][j]表示摆放好了前i行，且第i行状态为j的集合
    状态计算：f[i][a],  摆完了i行，第i行状态为a，第i-1行状态为b，第i行状态都相同，去掉第i行，由第i-1行转移而来
             f[i-1][b],摆完了i-1行，第i-1行状态为b
             f[i][a] += f[i-1][b]
             合法状态: 1.每个状态不能有两个相邻的1,
                      2. a & b == 0
*/
#include <iostream>
#include <vector>
using namespace std;

const int N = 14, M = 1 << 13, MOD = 1e8;
vector<int> state;  // 存放合法状态
vector<int> head[M];    // 存放每个状态可以转移的状态
int g[N];   // 存放每行土地
int f[N][M];
int n, m;

bool check(int state)
{
    for (int i = 0; i < m; i++)
        if ((state >> i & 1) && (state >> i + 1 & 1))
            return false;
    return true;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < m; j++)
        {
            int t;
            cin >> t;
            g[i] += !t << j;    // 1的地方不能种玉米，方便后边做与运算    
        }
    
    for (int i = 0; i < 1 << m; i++)
        if (check(i))
            state.push_back(i);

    for (int i = 0; i < state.size(); i++)
        for (int j = 0; j < state.size(); j++)
        {
            int a = state[i], b = state[j];
            if ((a & b) == 0)
                head[a].push_back(b);
        }
    
    f[0][0] = 1;    // 种了0行，状态为0的方案为1
    for (int i = 1; i <= n + 1; i++)
        for (int a : state)     // 当前状态
            for (int b : head[a])   // 上一行状态
            {
                if (a & g[i])   continue;
                f[i][a] = (f[i][a] + f[i - 1][b]) % MOD;
            }

    cout << f[n + 1][0] << endl;

    return 0;
}