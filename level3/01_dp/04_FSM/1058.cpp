// acwing 1058 股票买卖 V 
/*
    状态机模型
    状态表示: f[i][0]表示前i天，手上有货的利润，f[i][1]表示手上无货第1天的利润，f[i][2]表示手上无货>=2天的利润

    状态计算：
    f[i][0]
        有货 -> 有货
        有货 -> 无货第1天
    f[i][1]
        无货第1天 -> 无货>=2天
    f[i][2]
        无货>=2天 -> 无货>=2天
        无货>=2天 -> 有货
    f[i][0] = max(f[i-1][0], f[i-1][2]-w[i]);
    f[i][1] = f[i-1][0] + w[i];
    f[i][2] = max(f[i-1][1], f[i-1][2]);

    入口状态为f[i][2]，因为初试状态可以任意买入
    出口状态为max(f[n][1], f[n][2]),
    f[i][1]最终和f[i][2]一样，因此只需统计f[i][1]，但是如果股票价格单调下降，那么最大利润将会一直位于f[n][2]这个状态
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int f[N][3];
int w[N];
int n;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    f[0][0] = f[0][1] = -INF;
    f[0][2] = 0;
    for (int i = 1; i <= n; i++)
    {
        f[i][0] = max(f[i - 1][0], f[i - 1][2] - w[i]);
        f[i][1] = f[i - 1][0] + w[i];
        f[i][2] = max(f[i - 1][1], f[i - 1][2]);
    }

    cout << max(f[n][1], f[n][2]) << endl;

    return 0;
}