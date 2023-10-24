// acwing 874 筛法就欧拉函数
/*
    求1-n中每个数的欧拉函数，如果对每个数分解质因数，然后求，时间复杂度为O(n√n)
    用线性筛法求1-n的欧拉函数，时间复杂度为O(n)

    欧拉定理: 若a与n互质,则a^(φ(n)) ≡1 (mod n)
    费马定理: 若p为质数,则a^(p-1) ≡1 (mod p)

*/
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
int primes[N], cnt;
bool st[N];
int phi[N]; // 记录欧拉函数
int n;

LL get_eulers(int n)
{
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!st[i])
        {
            primes[cnt++] = i;
            phi[i] = i - 1; // 如果i是质数，那么φ(i)=i-1
        }

        for (int j = 0; primes[j] <= n / i; j++)
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0)
            {
                // 如果primes[j]是i的质因子，primes[j]这个质因子一定在i中出现过,那么φ(primes[j]*i)=primes[j]*φ(i)
                phi[primes[j] * i] = phi[i] * primes[j];
                break;
            }
            else
            {
                // 如果primes[j]不是i的质因子，primes[j]一定是primes[j]*i的质因子,
                // 那么φ(primes[j]*i)=primes[j]*φ(i)*(1-1/primes[j])
                phi[primes[j] * i] = phi[i] * (primes[j] - 1);
            }
        }
    }
    LL res = 0;
    for (int i = 1; i <= n; i++)
        res += phi[i];     
    return res;
}

int main()
{
    cin >> n;
    cout << get_eulers(n) << endl;

    return 0;
}