// acwing 866 试除法判定质数    试除法
/*
1.质数  2.约数  3.欧拉函数  4.快速幂    5.扩展欧几里得算法  6.中国剩余定理
*/
#include <iostream>
using namespace std;

// 试除法判断质数，O(sqrt(n))
bool is_prime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i <= n / i; i++) // 最好不要写i<=sqrt(n),sqrt时间复杂度较高,也不要写i*i<=n,如果i接近int，i*i超出int范围，变为负数
        if (n % i == 0)
            return false;
    return true;
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int a;
        cin >> a;
        if (is_prime(a))
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}