// acwing 143 最大异或对
/*
    如果暴力做就是两层循环，其中内层循环的目的就是找到在a0-ai-1中与ai异或最大的数
    找到与ai异或最大的数，通过一个trie树，从最高位往最低位开始遍历
    如果ai二进制第一位是1，那么就找trie树中第一位是0的，以此类推
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10, M = 31 * N;

int n;
int a[N];
int son[M][2], idx;

void insert(int x)
{
    int p = 0;
    for (int i = 30; i >= 0; i--)
    {
        int u = x >> i & 1; // x的二进制的第i位数字
        if (!son[p][u])
            son[p][u] = ++idx;
        p = son[p][u];
    }
}

int query(int x)
{
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i--)
    {
        int u = x >> i & 1;
        if (son[p][!u]) // 先往和u不同的方向走
        {
            p = son[p][!u];
            res = res * 2 + !u;
        }
        else
        {
            p = son[p][u];
            res = res * 2 + u;
        }
    }
    return res;
}

int main()
{
    scanf("%d", &n);
    int res = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    for (int i = 1; i <= n; i++)
    {
        insert(a[i]);
        int t = query(a[i]);
        res = max(res, t ^ a[i]);
    }

    printf("%d\n", res);
    return 0;
}