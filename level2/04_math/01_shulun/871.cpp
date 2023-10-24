// acwing 871 约数之和
/*
    一个数可以表示为N=p1^a1 * p2^a2 * p3^a3 * ... * pn^an,其中p1、p2、...pn都是质数
    则N的约数之和为(p1^0+p1^1+...+p1^a1)*...*(pk^0+pk^1+...+pk^ak)
*/
#include <iostream>
#include <math.h>
#include <unordered_map>
using namespace std;
const int mod = 1e9 + 7;
int n;

int main()
{
    cin >> n;
    unordered_map<int, int> primes;
    while (n--)
    {
        int x;
        cin >> x;
        for (int i = 2; i <= x / i; i++)
        {
            if (x % i == 0)
                while (x % i == 0)
                {
                    x /= i;
                    primes[i]++;
                }
        }
        if (x > 1)
            primes[x]++;
    }

    long long res = 1;
    for (auto x : primes)
    {
        int base = x.first, p = x.second;
        long long ans = 1;
        for (int i = 0; i < p; i++)
            ans = (ans * base + 1) % mod;
        
        res = res * ans % mod;
    }
    cout << res << endl;

    return 0;
}
