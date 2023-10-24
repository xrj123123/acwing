// acwing 1064 小国王
/*
    棋盘式的状态压缩dp
    和蒙德里安的猜想一样属于棋盘式状态压缩dp，蒙德里安是摆放1*2的方块，这道题相当于摆放3*3的方格
    状态表示: f[i][j][s],摆放了前i行，用了j个国王，且这一行的状态为s的方案数
    状态计算: 因为i-2行对第i行没影响，因此从第i-1行转移而来
             摆放第i行: 已经摆完了i行，且第i行状态为a，用了j个国王，第i-1行状态为b,(第i行都相同，去掉可以转化为下面方案)
             摆放第i-1行：已经摆完了i-1行，且第i-1行状态为b,用了j-count(a)个国王的方案数
             f[i][j][a] += f[i-1][j-count(a)][b]

    合法方案: 第i-1行内部不能有两个1相邻
             第i-1行和第i行之间也不能相互攻击到
                a,b
                (a & b) == 0
                (a | b)不能有两个相邻的1
*/
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;

const int N = 12, M = 1 << 10, K = 110;
int n, m;
vector<int> state;  // state用来存合法的数量
vector<int> head[M];    // 每种状态可以转移到的其他状态
int cnt[M]; // 每种状态中1的个数
LL f[N][K][M];

bool check(int x)
{
    for (int i = 0; i < n - 1; i++)
        if ((x >> i & 1) && (x >> i + 1 & 1))
            return false;
    return true;
}

int count(int x)
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (x >> i & 1)
            cnt++;
    return cnt;
}

int main()
{
    cin >> n >> m;

    // 先处理合法的状态
    for (int i = 0; i < 1 << n; i++)
        if (check(i))
        {
            state.push_back(i);
            cnt[i] = count(i);
        }
    
    // 处理某个状态可以转移到的状态
    for (int i = 0; i < state.size(); i++)
        for (int j = 0; j < state.size(); j++)
        {
            int a = state[i], b = state[j];
            if (!(a & b) && check(a | b))
                head[a].push_back(b);
        }
    
    // 摆了0行，用了0个国王，状态为0的方案数为1
    f[0][0][0] = 1;
    // 如果i枚举到n，最后答案需要枚举f[n][m][i],i枚举到n+1,结果直接输出f[n+1][m][0]即可
    for (int i = 1; i <= n + 1; i++)    
        for (int j = 0; j <= m; j++)
            for (int a : state)
                for (int b : head[a])
                {
                    int c = cnt[a];
                    if (j >= c)
                        f[i][j][a] += f[i - 1][j - c][b];
                }
    cout << f[n + 1][m][0] << endl;

    return 0;
}