// acwing 1023 买书
/*
    f[i][j]表示前i本书(每本书数量无限多)，价值恰好为j的方案数
    f[i][j]   = f[i-1][j] + f[i-1][j-v*1] + f[i-1][j-v*2] + ... + f[i-1][j-v*s];
    f[i][j-v] =             f[i-1][j-v*1] + f[i-1][j-v*2] + ... + f[i-1][j-v*s];
    f[i][j] = (f[i-1][j] + f[i][j-v]);

    f[0][0] = 1; 其余为0
*/
#include <iostream>
using namespace std;

const int  N = 1010;
int f[N];
int a[4] = {10, 20, 50, 100};
int n;

 
int main()
{
    cin >> n;
    f[0] = 1;
    for (int i = 0; i < 4; i++)
        for (int j = a[i]; j <= n; j++)
            f[j] += f[j - a[i]];
    
    cout << f[n] << endl;

    return 0;
}