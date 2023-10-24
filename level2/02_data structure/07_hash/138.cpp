// acwing 138 兔子与兔子
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e6 + 10, P = 131;
typedef unsigned long long ULL;
ULL h[N], p[N]; // h[i]表示前i个字符的hash值，p[i]表示P^i
char s[N];
int m;

int get(int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main()
{
    scanf("%s", s + 1);
    scanf("%d", &m);
    int len=strlen(s + 1);      // strlen时间复杂度为O(n),所以要先计算写外边
    p[0]=1;
    for (int i = 1; i <= len; i++)
    {
        p[i] = p[i - 1] * P;
        h[i] = h[i - 1] * P + s[i];
    }

    while (m--)
    {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if (get(l1, r1) == get(l2, r2))
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}