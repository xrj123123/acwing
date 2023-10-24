// acwing 1018 最低通行费
#include <iostream>
using namespace std;

const int N = 110;
int w[N][N], f[N][N];
int n;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> w[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (j == 1)
                f[i][j] = f[i - 1][j] + w[i][j];
            else if (i == 1)
                f[i][j] = f[i][j - 1] + w[i][j];
            else
                f[i][j] = min(f[i - 1][j], f[i][j - 1]) + w[i][j];
        }

    cout << f[n][n] << endl;

    return 0;
}