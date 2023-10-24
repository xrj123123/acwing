// acwing 1022 宠物小精灵
/*
f[i][j][k]表示前i个小精灵,精灵球数为j,体力为k时的最大值
*/
#include <iostream>
using namespace std;

const int N = 1010, M = 510;
int f[N][M];
int v[N], d[N];
int n, m, s;

int main()
{
    cin >> n >> m >> s;

    for (int i = 1; i <= s; i++)
        cin >> v[i] >> d[i];
    
    for (int i = 1; i <= s; i++) // s个小精灵
        for (int j = n; j >= v[i]; j--) // n个精灵球
            for (int k = m - 1; k >= d[i]; k--) // m的体力 体力不能等于0，所以要从m-1开始
                f[j][k] = max(f[j][k], f[j - v[i]][k - d[i]] + 1);

    cout << f[n][m - 1] << " ";

    int res = m - 1;
    for (int k = 0; k < m; k++)
    {
        if (f[n][k] == f[n][m - 1])
        {
            res = k;
            break;
        }
    }
  
    cout << m - res << endl;

    return 0;
}