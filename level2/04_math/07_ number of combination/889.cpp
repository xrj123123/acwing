// acwing 889 满足条件的01序列
/*
    n个0和n个1,满足任意前缀序列中 0 的个数都不少于 1 的个数
    可以转化到坐标轴里，0表示向右走，1表示向左走，因此解就是从(0,0)走到(n,n)且路径在y=x之下的方案数
    可以用总方案数 - 经过y=x+1(y=x上面的一条直线)的方案数，经过y=x+1直线的那个点做y=x的轴对称线
    比如n=6,目标是走到(6,6)，经过y=x+1后，之后的路径做y=x的轴对称，即走到(5,7)，用走到(6,6)的方案数-走到(5,7)的方案数即为答案
    C(12,6)-C(12,5) --> C(2n,n)-C(2n,n-1) = C(2n,n)/n+1  卡特兰数
*/
#include <iostream>
using namespace std;
typedef long long LL;
const int mod = 1e9 + 7;

int qmi(int a, int k, int p)
{
    int res = 1;
    while (k)
    {
        if (k & 1)
            res = (LL)res * a % p;
        k >>= 1;
        a = (LL)a * a % p;
    }
    return res;
}

int main()
{
    int n;
    cin >> n;

    // C(2n,n)-C(2n,n-1) = C(2n,n)/n+1 = 2n!/(n!*n!* n+1)
    int res = 1;
    int a = 2 * n, b = n;
    for (int i = a; i > b; i--)
        res = (LL)res * i % mod;

    for (int i = 1; i <= n; i++)
        res = (LL)res * qmi(i, mod - 2, mod) % mod;

    res = (LL)res * qmi(n + 1, mod - 2, mod) % mod;
    cout << res << endl;

    return 0;
}