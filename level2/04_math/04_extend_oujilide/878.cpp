// acwing 878 线性同余方程
/*
    给定a,b,m,求x,使得a*x ≡ b (mod m)
    a*x ≡ b (mod m) --> a*x = m*y + b --> a*x - m*y = b --> a*x + m*y' = b
    若a*x + m*y' = b 有解，则 (a,m)|b
    即求出 a*x + m*y' = (a,m) ,然后左右同时扩大到b/(a,m)倍
    所以只要b是(a,b)的倍数就有解
*/
#include <iostream>
using namespace std;
typedef long long LL;

int exgcd(int a, int b, int &x, int &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }

    int d = exgcd(b, a % b, y, x);
    y = y - a / b * x;
    return d;
}

int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int a, b, m;
        scanf("%d%d%d", &a, &b, &m);
        int x, y;
        int d = exgcd(a, m, x, y);
        if (b % d)
            puts("impossible");
        else
            printf("%d\n", (LL)x * (b / d) % m);
    }

    return 0;
}