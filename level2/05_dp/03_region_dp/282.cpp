// acwing 828 石子合并

/* dp[i][j]表示将第i堆到第j堆合并起来所需最小代价 */

#include <iostream>
#include <cstring>
using namespace std;
const int N = 310;
int s[N], dp[N][N];
int n, num;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> num;
        s[i] = s[i - 1] + num;
    }

    memset(dp, 0x3f, sizeof(dp));

    // 区间dp，第一层枚举长度，第二层枚举起点
    for (int len = 1; len <= n; len++)
    { // 区间长度
        for (int i = 1; i + len - 1 <= n; i++)  // 起点
        {                        
            int j = i + len - 1; // 终点

            if (len == 1)
            {
                dp[i][j] = 0;
                continue;
            }

            for (int k = i; k < j; k++)
            {
                dp[i][j] = min(dp[i][k] + dp[k + 1][j] + s[j] - s[i - 1], dp[i][j]);
            }
        }
    }
    cout << dp[1][n] << endl;

    return 0;
}