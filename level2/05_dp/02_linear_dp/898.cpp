// acwing 898 数字三角形
#include <iostream>
using namespace std;
const int num = 510;
int a[num][num], dp[num][num];

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= i + 1; j++)
        {
            dp[i][j] = -0x3f3f3f3f;
        }
    }
    dp[1][1] = a[1][1];
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + a[i][j];
        }
    }

    int res = -0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
    {
        res = max(res, dp[n][i]);
    }
    cout << res << endl;
    return 0;
}