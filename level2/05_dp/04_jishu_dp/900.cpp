// acwing 900 整数划分
/*
    将n划分为n1 + n2 + ... +nk,且n1>=n2>=...>=nk
    即在1-n，这n个数中任选，使其和为n
    可以转化为完全背包问题

    状态表示: f[i][j] 表示从1-i中选使其和为j的选法数量

    状态计算: 通过枚举选几个i来计算f[i][j]
    f[i][j] = f[i-1][j] + f[i-1][j-i] + f[i-1][j-2*i] +...+ f[i-1][j-k*i]
    优化
    f[i][j-i] =           f[i-1][j-i] + f[i-1][j-2*i] +...+ f[i-1][j-k*i]
    因此f[i][j] = f[i-1][j] + f[i-1][j-i]
    一维优化: f[j] = f[j] + f[j-i]
*/
/* #include <iostream>
using namespace std;
const int N = 1010, mod = 1e9 + 7;
int f[N];
int n;

int main()
{
    cin >> n;
    f[0] = 1; // 前0件物品，体积恰好是0，只有一种方案;  f[j],如果体积不超过j,则f[j]=1

    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            f[j] = (f[j] + f[j - i]) % mod;

    cout << f[n] << endl;

    return 0;
} */

// 第二种划分方法
/*
    状态表示: f[i][j] 表示总和为i，并恰好由j个数组成，的方案数

    状态计算: f[i][j]划分: 1.最小值为1     f[i][j] = f[i-1][j-1], i减去1，j-1个数，加上1既是f[i][j]的方案数
                          2.最小值大于1   f[i][j] = f[i-j][j], 因为最小值大于1，所以将每个数都减1，方案数还等于f[i][j]
             f[i][j] = f[i-1][j-1] + f[i-j][j]
*/
#include <iostream>
using namespace std;
const int N = 1010, mod = 1e9 + 7;
int f[N][N]; // f[i][j] 表示总和为i用j个数来表示的方案数
int n;

int main()
{
    cin >> n;

    f[0][0] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            f[i][j] = (f[i - 1][j - 1] + f[i - j][j]) % mod;

    int res = 0;
    for (int i = 1; i <= n; i++)
        res = (res + f[n][i]) % mod;

    cout << res << endl;

    return 0;
}