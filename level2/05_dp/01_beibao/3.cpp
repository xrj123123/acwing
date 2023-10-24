// acwing 3 完全背包问题
/*
    朴素做法:f[i][j] = f[i-1,j-v[i]*k]+w[i]*k

    f[i,j] = max(f[i-1,j], f[i-1,j-v]+w, f[i-1,j-2*v]+2*w, f[i-1,j-3*v]+3*w,...)
    f[i,j-v] = max(        f[i-1,j-v],   f[i-1,j-2*v]+w,   f[i-1.j-3*v]+2*w,...)
    因此
    f[i,j] = max(f[i-1,j], f[i,j-v]+w);
*/
/*
#include <iostream>
using namespace std;
const int N = 1010;
int v[N], w[N];
int f[N][N];
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
        {
            f[i][j] = f[i - 1][j];
            if (j >= v[i])
                f[i][j] = max(f[i][j], f[i][j - v[i]] + w[i]);
        }

    cout << f[n][m] << endl;

    return 0;
} */

/*
    一维优化:和01背包一样，第i层1只与第i-1层有关，所以第一维可以去掉
    这里内层循环是正序，j-v[i]<j,因此是从第i层更新的，这正是完全背包所需要的
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
        for (int j = v[i]; j <= m; j++)
            f[j] = max(f[j], f[j - v[i]] + w[i]);

    cout << f[m] << endl;

    return 0;
}
