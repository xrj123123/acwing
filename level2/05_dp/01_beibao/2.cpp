/* // acwing 2 01背包问题
#include <iostream>
using namespace std;
const int N = 1010;
int v[N], w[N];
int f[N][N]; // f[i][j]表示前i件物品容积为j时可以装的最大值
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            f[i][j] = f[i - 1][j];
            if (j >= v[i])
                f[i][j] = max(f[i - 1][j], f[i - 1][j - v[i]] + w[i]);
        }

    cout << f[n][m] << endl;
    return 0;
}
 */

// acwing 2 01背包问题
/*
    f[i][j] = f[i - 1][j];
    if (j >= v[i])
        f[i][j] = max(f[i - 1][j], f[i - 1][j - v[i]] + w[i]);

    因为f[i][j]之和第i-1层有关，所以可以去掉，f[i][j] = f[i - 1][j]; --> f[j] = f[j];直接去掉
    if (j >= v[i])，所以j直接从v[i] - m，
    for (int j = v[i]; j <= m; j++)
        f[j] = max(f[j], f[j - v[i]] + w[i]);
    这样显然不对，这样表示
        f[j] = max(f[j], f[j - v[i]] + w[i]);
        f[i][j] = max(f[i][j], f[i][j - v[i]] + w[i]); 因为j-v[i] < j ,所以f[j - v[i]] + w[i]一定是在第i层更新的
        所以内层要逆序更新,这样在计算f[j]时，f[j-v[i]]还没有被更新过，就是第i-1层的f[j-v[i]]
*/
#include <iostream>
using namespace std;
const int N = 1010;
int v[N], w[N];
int f[N];
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);

    cout << f[m] << endl;
    return 0;
}