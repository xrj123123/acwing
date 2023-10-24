// acwing 895 最大上升子序列
#include <iostream>
using namespace std;
int n;
int a[1010];
int dp[1010];
int g[1010];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        dp[i] = 1;
    }

    for (int i = 2; i <= n; i++)
    {
        g[i] = 0;
        for (int j = 1; j < i; j++)
        {
            if (a[i] > a[j])
            {
                if (dp[j] + 1 > dp[i])
                {
                    g[i] = j;
                    dp[i] = dp[j] + 1;
                }
            }
        }
    }
    int res = 0;
    int k = 1;
    for (int i = 1; i <= n; i++)
    {
        if (dp[i] > res)
        {
            res = dp[i];
            k = i;
        }
    }

    for (int i = 1; i <= res; i++)
    {
        cout << a[k] << " ";
        k = g[k];
    }
    cout << endl;
    cout << res << endl;

    return 0;
}