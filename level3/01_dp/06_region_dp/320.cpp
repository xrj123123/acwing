// acwing 320 能量项链
/*
    和环形石子合并类似
    这道题假如给出数据是2 3 5 10，实际是(2,3),(3,5),(5,10),(10,2),展开是2 3 5 10 2，长度为n+1
    状态表示：f[i,j]表示合并从i到j之间珠子获得能量的最大值
    状态计算：f[i,j] = f[i,k] + f[k,j] + i*k*j;  (k∈[i+1, j-1])
*/
#include <iostream>
using namespace std;

const int N = 210;
int a[N];
int f[N][N];
int n;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i + n] = a[i];
    }

    for (int len = 3; len <= n + 1; len++)
        for (int l = 1; l + len - 1 <= 2 * n; l++)
        {
            int r = l + len - 1;
            for (int k = l + 1; k < r; k++)
                f[l][r] = max(f[l][r], f[l][k] + f[k][r] + a[l] * a[k] * a[r]);
        }

    int res = -1;
    for (int i = 1; i <= n; i++)
        res = max(res, f[i][i + n]);
    
    cout << res << endl;

    return 0;
}