// acwing 877 扩展欧几里得算法
/*
裴蜀定理:
对于任意正整数a,b，一定存在非零整数x，y，使得ax+by=(a,b) ，a和b的最大公因数，且(a,b)是a和b能凑出来的最小正整数

(a,b)=(b,a%b)
*/
#include <iostream>
using namespace std;

// 扩展欧几里得算法，使ax+by=(a,b)
int exgcd(int a, int b, int &x, int &y)
{
    if (!b) // b=0, (a,0)=a, ax+by=a
    {
        x = 1, y = 0;
        return a;
    }
    /*
        递归结束后，应该得到 b*y + (a%b)*x = d  (a,b)
        其中a%b=a-[a/b]*b,代入得 b*y + (a-[a/b]*b)*x = d
        a*x + b*(y-[a/b]*x) = d
    */
    int d = exgcd(b, a % b, y, x);
    // a的系数不变
    y = y - a / b * x;
    return d;
}

int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int a, b, x, y;
        scanf("%d%d", &a, &b);
        exgcd(a, b, x, y);
        printf("%d %d\n", x, y);
    }

    return 0;
}