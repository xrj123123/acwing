// acwing 876 快速幂求逆元
/*
    b与p互质，b*x ≡1 (mod p)  则x是b的逆元
    p是质数，由费马定理b^(φ(p)) ≡1 (mod p),即b^(p-1) ≡1 (mod p) --> b*b^(p-2) ≡1 (mod p)
    无解情况:b是p的倍数，此时bx也是p的倍数，mod p=0，因为p是质数，所以b只要不是p的倍数就和p互质

    b 存在乘法逆元的充要条件是 b 与模数 m 互质。当模数 m 为质数时，b^(m−2) 即为 b 的乘法逆元

    如果p是质数，直接用费马定理求逆元，如果p不是质数，就只能用扩展欧几里得算法求逆元
*/
#include <iostream>
typedef long long LL;
using namespace std;

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
    scanf("%d", &n);
    while (n--)
    {
        int a, p;
        scanf("%d%d", &a, &p);
        if (a % p)
            printf("%d\n", qmi(a, p - 2, p));
        else
            printf("%s\n", "impossible");
    }

    return 0;
}