// acwing 1057 股票买卖 IV
/*
    状态机模型
    状态表示: f[i][j][0]表示前i天，交易完成j次，当前手中无货得到的利润
             f[i][j][1]表示前i天，正在进行第j次交易，当前手中有货得到的利润
    状态计算:
        f[i][j][1]  
            有货 -> 有货    前i-1天正在进行第j次，第i天不卖
            无货 -> 有货    前i-1天完成了j-1次，第i天买了，进行第j次
            f[i][j][1] = max(f[i-1][j][1], f[i-1][j-1][0]-w[i]);
        f[i][j][0]
            无货 -> 无货    第i-1天不买，第i天还不买
            有货 -> 无货    第i天卖出
            f[i][j][0] = max(f[i-1][j][0], f[i-1][j][1]+w[i]);
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5 + 10, M = 110;
int f[M][2];
int w[N];
int n, m;

int main()
{
    cin >> n >> m;
    // 前i天完成0次，手中有货状态不存在，前i天完成0次，手中无货，获得利润为0
    memset(f, -0x3f, sizeof f);
    f[0][0] = 0;

    for (int i = 1; i <= n; i++)
        cin >> w[i];

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
        {
            f[j][0] = max(f[j][0], f[j][1] + w[i]);
            f[j][1] = max(f[j][1], f[j - 1][0] - w[i]);
        }
    
    int res = 0;
    for (int j = 1; j <= m; j++)
        res = max(res, f[j][0]);

    cout << res << endl;

    return 0;
}