// acwing 204 表达整数的奇怪方式    中国剩余定理
/*
m1,m2,...mk两两互质

x ≡ a1 (mod m1)
x ≡ a2 (mod m2)
...
x ≡ ak (mod mk)

M=m1*m2*...*mk
Mi=M/mi (除了mi之外，其他m的乘积)   Mi^-1表示Mi mod mi的逆
x=a1*M1*M1^-1 + a2*M2*M2^-1 + ... +ak*Mk*Mk^-1
*/
#include <iostream>
using namespace std;
typedef long long LL;
int n;

LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }

    LL d = exgcd(b, a % b, y, x);
    y = y - a / b * x;
    return d;
}

int main()
{
    scanf("%d", &n);

    bool flag = true;
    LL a1, m1; // x = k1*a1 + m1    x ≡ a1 (mod m1)
    scanf("%d%d", &a1, &m1);

    for (int i = 0; i < n - 1; i++) // 每次将两个式子合并为一个，共合并n-1次
    {
        LL a2, m2; // x = k2*a2 + m2
        /*
            k1*a1 + m1 = k2*a2 + m2
            k1*a1 - k2*a2 = m2 - m1  有解的前提是(a1,a2)|m2-m1

            k1 = k1 + k* a2/d   k2 = k2 + k* a1/d
            x=a1 * (k1 + k* a2/d) +m1 = a1 * k1 + m1 +k* a1*a2/d
            x=a1 * (k1 + k* a2/d) +m1 = a1 * k1 + m1 +k[a1,a2]  = m1 + k*a  这样两个式子就合并为1个
        */
        scanf("%d%d", &a2, &m2);

        LL k1, k2;
        LL d = exgcd(a1, a2, k1, k2);
        if ((m2 - m1) % d) // m2-m1 不是d的倍数
        {
            flag = false;
            break;
        }

        k1 *= (m2 - m1) / d; // 尽量让k1为最小
        LL t = a2 / d;       // k1 = k1 + k* a2/d
        k1 = (k1 % t + t) % t;

        m1 = a1 * k1 + m1; // x = a1 * k1 + m1 +k[a1,a2]
        // a1 = abs(a1 / d * a2);
        a1 = a1 * a2 / d;
    }

    if (flag)
        cout << (m1 % a1 + a1) % a1 << endl; // x = m1 + k*a
    else
        puts("-1");
    return 0;
}
