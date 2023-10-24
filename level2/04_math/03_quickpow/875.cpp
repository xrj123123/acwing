// acwing 875 快速幂    O(logk)
#include <iostream>
using namespace std;
typedef long long LL;
int n;

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
    scanf("%d", &n);
    while (n--)
    {
        int a, k, p;
        scanf("%d%d%d", &a, &k, &p);
        printf("%d\n", qmi(a, k, p));
    }
}
