// acwing 887 求组合数 III
/*
    n的范围为20，a、b的范围为10^18，p的范围为10^5   O(log(p,n)*p*logp) n为a、b范围
    使用卢卡斯定理: C(a,b) ≡ C(a mod p,b mod p)*C(a/p,b/p) (modp)，然后直接处理阶乘即可计算
*/
#include <iostream>
typedef long long LL;
using namespace std;
int p;

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

// C(a,b) = (a-b+1)! / b!
int C(int a, int b)
{
    int res = 1;
    for (int i = 1, j = a; i <= b; i++, j--)
    {
        res = (LL)res * j % p;
        res = (LL)res * qmi(i, p - 2, p) % p;
    }
    return res;
}

int lucas(LL a, LL b)
{
    if (a < p && b < p)
        return C(a, b);
    else
        return (LL)C(a % p, b % p) * lucas(a / p, b / p) % p;
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        LL a, b;
        cin >> a >> b >> p;
        cout << lucas(a, b) << endl;
    }

    return 0;
}