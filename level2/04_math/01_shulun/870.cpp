// acwing 870 约数个数
/*
    一个数可以表示为N=p1^a1 * p2^a2 * p3^a3 * ... * pn^an,其中p1、p2、...pn都是质数
    则N的约数个数为(a1+1)*(a2+1)*...*(an+1)
    int范围内，约数最多的个数约为1500
*/
#include <iostream>
#include <unordered_map>
using namespace std;
const int mod = 7 + 1e9;
int n;
unordered_map<int, int> primes;

void number(int x)
{
    for (int i = 2; i <= x / i; i++)
    {
        if (x % i == 0)
        {
            while (x % i == 0)
            {
                primes[i]++;
                x /= i;
            }
        }
    }
    if (x > 1)
        primes[x]++;
}

int main()
{
    cin >> n;
    while (n--)
    {
        int a;
        cin >> a;
        number(a);
    }

    long long res = 1;
    for (auto x : primes)
        res = res * (x.second + 1) % mod;
    cout << res << endl;

    return 0;
}