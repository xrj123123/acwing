// acwing 873 欧拉函数
/*
    欧拉函数：φ(n)表示1-n中与n互质的数的个数    时间复杂度主要是分解质因数的时间复杂度为O(sqrt(n))
    N=p1^a1 * p2^a2 * p3^a3 * ... * pn^an
    φ(N)=N*(1-1/p1)*(1-1/p2)*...*(1-1/pn)
*/
#include <iostream>
using namespace std;
int n;

int oula(int x)
{
    int res = x;
    for (int i = 2; i <= x / i; i++)
    {
        if (x % i == 0)
        {
            res = res / i * (i - 1);    // 不能有小数，所以要这样运算
            while (x % i == 0)
                x /= i;
        }
    }
    if (x > 1)
        res = res / x * (x - 1);
    return res;
}

int main()
{
    cin >> n;
    while (n--)
    {
        int a;
        cin >> a;
        int res = oula(a);
        cout << res << endl;
    }

    return 0;
}