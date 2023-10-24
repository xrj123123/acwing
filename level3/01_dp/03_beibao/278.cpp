// acwing 278 数字组合
/*
    将每个数字的大小看做体积
    f[i][j] 表示从前i个数中选，和等于j的方案数
    f[i][j] = f[i-1][j] + f[i-1][j-a[i]]

    求得是和恰好等于j，因此f[0][0]=1,其余都是0
*/
#include <iostream>
#include <cstring>
using namespace std;

const int N = 10010;
int f[N];
int n, m;

int main()
{
    cin >> n >> m;
    f[0] = 1;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        for (int j = m; j >= a; j--)
            f[j] += f[j - a];
    }

    cout << f[m] << endl;

    return 0;
}
