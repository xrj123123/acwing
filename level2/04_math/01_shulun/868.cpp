// acwing 868 筛质数
#include <iostream>
using namespace std;
const int N = 1e6 + 10;
bool st[N]; // st[i]表示i是否被筛过,没被筛过说明是素数
int prime[N], n, cnt;

// 埃及筛
/*
void get_prime(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!st[i]) // 当前数是素数
        {
            prime[cnt++] = i;
            for (int j = i + i; j <= n; j += i)
                st[j] = true;
        }
    }
}
*/

// 线性筛法     n只会被最小质因子筛掉
/*
    1.i%p[j]==0
        p[j]一定是i的最小质因子,p[j]一定是p[j]*i的最小质因子
    2.i%p[j]!=0
        p[j]一定小于i的所有质因子,p[j]也一定是p[j]*i的最小质因子

    对于一个合数x,假设p[j]是x的最小质因子，当i枚举到x/p[j]的时候,一定会被筛掉

    每个数都是用他的最小质因子筛，每个数只有一个最小质因子，所以每个数只会被筛一次，因此效率高
*/
void get_prime(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!st[i])
            prime[cnt++] = i;
        // prime[j]<=n/i --> prime[j]*i<=n,求得是n以内的,大于n就没必要枚举了
        // 这里不用加上j<=cnt,因为如果i是合数,那么枚举到i的最小质因子时就停止了
        // 如果i为质数，那么枚举到i本身就停止了，所以不需要加上j<=cnt
        for (int j = 0; prime[j] <= n / i; j++)
        {
            st[prime[j] * i] = true;
            // i%prime[j]时需要退出，此时prime[j]是最小质因子，如果不退出，到prime[j+1]时就不是最小质因子了，就会重复筛
            if (i % prime[j] == 0)
                break; // prime[j]一定是i的最小质因子，因此也是prime[j]*i的最小质因子
        }
    }
}

int main()
{
    scanf("%d", &n);
    get_prime(n);
    printf("%d\n", cnt);

    return 0;
}