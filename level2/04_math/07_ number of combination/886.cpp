// acwing 886 求组合数 II
/*
    n范围为10000，a、b范围为1e5,因此需要预处理阶乘  O(nlog(n))  n为a、b范围
    C(a,b) = a! / (a-b)!*b!
    fact[i]=i! (mod 1e9+7)
    infact[i]=(i!)^-1 (mod 1e9+7)
    C(a,b)=fact[a] / infact[a-b]*infact[b]
*/
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10, mod = 1e9 + 7;
int fact[N], infact[N];

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
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fact[i] = (LL)fact[i - 1] * i % mod;
        // k! * x ≡ 1 (mod p) -> k(k-1)..1 * x  ≡ 1 (mod p) -> x = k(k-1)..1 ^(p-2) (mod p)
        infact[i] = (LL)infact[i - 1] * qmi(i, mod - 2, mod) % mod;
    }
    int n;
    cin >> n;
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        // C(a,b) = fact(a)*infact(a-b)*infact(b)
        // 三个连续相乘会超出long long 范围
        int res = (LL)fact[a] * infact[a - b] % mod * infact[b] % mod;
        cout << res << endl;    
    }

    return 0;
}