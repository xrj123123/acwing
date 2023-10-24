// acwing 867 分解质因数
#include <iostream>
using namespace std;
int n;

void devide(int n)
{
    for (int i = 2; i <= n / i; i++)
    {
        if (n % i == 0)
        {
            int s = 0;
            while (n % i == 0)
            {
                s++;
                n /= i;
            }
            printf("%d %d\n", i, s);
        }
    }
    if (n > 1) // 如果存在一个大于n/i的质数，那么最后输出
        printf("%d %d\n", n, 1);
    puts("");
}

int main()
{
    scanf("%d", &n);
    while (n--)
    {
        int x;
        scanf("%d", &x);
        devide(x);
    }

    return 0;
}