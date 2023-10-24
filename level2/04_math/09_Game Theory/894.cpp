// acwing 894 拆分-Nim游戏
/*
    拿走每一堆，都会拿来两堆，相当于将a1分为(b1,b2),且b1<a1,b2<a1, sg(b1+b2)=sg(b1)^sg(b2)
    多个独立局面的SG值，等于这些局面SG值的异或和
*/
#include <iostream>
#include <unordered_set>
#include <cstring>
using namespace std;
const int N = 110;
int f[N];

int sg(int x)
{
    if (f[x] != -1)
        return f[x];
    unordered_set<int> S;
    for (int i = 0; i < x; i++)
        for (int j = 0; j <= i; j++)
            S.insert(sg(i) ^ sg(j));
    
    for (int i = 0;; i++)
        if (!S.count(i))
            return f[x] = i;
}

int main()
{
    int n;
    cin >> n;
    int res = 0;
    memset(f, -1, sizeof f);
    while (n--)
    {
        int x;
        cin >> x;
        res = res ^ sg(x);
    }
    if (res)
        puts("Yes");
    else
        puts("No");
}
