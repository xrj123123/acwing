// acwing 899 编辑距离
/*
    n个字符串，m次询问，每次编辑距离时间复杂度为n^2,总共时间复杂度为10^8
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 15, M = 1010;
int f[N][N];
char a[M][N];
int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", a[i] + 1);

    while (m--)
    {
        char b[N];
        int limit;
        scanf("%s%d", b + 1, &limit);

        int res = 0;
        memset(f, 0, sizeof f);
        for (int i = 0; i < n; i++)
        {
            int len1 = strlen(a[i] + 1);
            int len2 = strlen(b + 1);
 
            for (int k = 1; k <= len2; k++)
                f[0][k] = k;
            for (int k = 1; k <= len1; k++)
                f[k][0] = k;

            for (int k = 1; k <= len1; k++)
                for (int j = 1; j <= len2; j++)
                {
                    f[k][j] = min(f[k - 1][j] + 1, f[k][j - 1] + 1);
                    if (a[i][k] != b[j])
                        f[k][j] = min(f[k][j], f[k - 1][j - 1] + 1);
                    else
                        f[k][j] = min(f[k][j], f[k - 1][j - 1]);
                }
            if (f[len1][len2] <= limit)
                res++;
        }
        cout << res << endl;
    }

    return 0;
}
