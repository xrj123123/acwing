// acwing 861 二分图的最大匹配
/*
    左边集合为男生,右边集合为女生,想将一男一女匹配起来，求最大匹配数量
    从左边第一个男生开始，找他想匹配的女生，如果当前女生没有匹配，就将他们两个匹配
    如果当前女生匹配了，就找到和该女生匹配的男生，如果他可以匹配另一个，则他去匹配另一个，然后他们两个匹配
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 510, M = 1e5 + 10;
int h[N], e[M], ne[M], idx;
int match[N]; // match[i]表示第i个女生匹配的男生的编号
bool st[N];   // st[i]表示第i个女生是否被某个男生匹配过
int n1, n2, m;

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool find(int x) // 返回第x个男生是否可以匹配到女生
{
    for (int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            st[j] = true;
            if (match[j] == 0 || find(match[j]))    // 如果当前女生没有匹配或者和当前女生匹配的男生可以和另一个女生匹配
            {
                match[j] = x;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    scanf("%d%d%d", &n1, &n2, &m);
    memset(h, -1, sizeof h);
    while (m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
    }

    int cnt = 0;
    for (int i = 1; i <= n1; i++) // 枚举每个男生
    {
        memset(st, false, sizeof st);
        if (find(i))
            cnt++;
    }
    printf("%d\n", cnt);

    return 0;
}