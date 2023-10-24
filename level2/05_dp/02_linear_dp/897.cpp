// acwing 897 最长公共子序列
#include <iostream>
using namespace std;
int n, m;
char a[1010], b[1010];
int dp[1010][1010];
int main()
{
    cin >> n >> m;
    scanf("%s%s", a + 1, b + 1);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (a[i] == b[j])
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
        }
    }

    cout << dp[n][m] << endl;

    return 0;
}