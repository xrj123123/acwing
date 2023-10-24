// acwing 841 字符串哈希
// str="ABABA"  h[0]=0; h[1]='A'的哈希值;  h[2]='AB'的哈希值;   h[3]='ABC'的哈希值
// 将字符串看做是一个p进制的数
// P=131或13331，Q=2^64，可以假定不会出现冲突   使用unsigned long long就不需要取模，溢出就自动对2^64取模
#include <iostream>
using namespace std;
typedef unsigned long long ULL;
const int N = 1e5 + 10, P = 131;
ULL h[N], p[N]; // h[i]表示前i个字母的hash值，p[i]表示p^i

int get(int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main()
{
    int n, m;
    char str[N];
    scanf("%d%d%s", &n, &m, str + 1);

    p[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        p[i] = p[i - 1] * P;
        h[i] = h[i - 1] * P + str[i];
    }

    while (m--)
    {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if (get(l1, r1) == get(l2, r2))
            printf("%s\n", "Yes");
        else
            printf("%s\n", "No");
    }

    return 0;
}
