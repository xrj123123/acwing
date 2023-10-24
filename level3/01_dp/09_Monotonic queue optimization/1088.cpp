// acwing 1088 旅行问题
/*
    单调队列
    将这个环形公路拆成一条链，即1 2 3 4 1 2 3 4

    对于顺时针行走一圈，假设起点为1，终点为第2个1, 即从1 2 3 4 1走一圈，途中油量不能小于0
    就是判断从1走到1的前缀和中，不能有小于0的，对于每个点，o[i]表示当前点汽油，d[i]表示当前点到下一个点距离，
    o[i]-d[i]表示从当前点走到下一个点可以剩余的油量
    前缀和s[i]表示前i个点的剩余油量。
    如果起点i=2，长度n=4，那么就是在[i, i+n-1]中任何一个j，s[j] - s[i-1] > 0，即在[i, i+n-1]中找到最小的s[j],让s[j]大于s[i-1]就可以走一圈
    因为是顺时针枚举起点，枚举到第i个起点的时候，它需要用到它后边n个点的最小值，因此需要逆向枚举

    对于逆时针，o[i]-d[i-1]表示当前点走到下一个点可以剩余的油量
    这时需要求后缀和，如果起点i=2(后边的2)，长度n=4，就是在[i-n+1, i]中找到任何一个j，使得s[j]-s[i+1] > 0，
    即在[i-n+1, i]中招待最小的s[j],让s[j] > s[i+1]，才可以走一圈，因为是逆时针枚举起点，当枚举到第i个点时，需要用到它前n个点，所以要顺时针枚举
*/
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 2e6 + 10;
LL s[N];
int d[N], o[N], q[N];
bool ans[N];
int n;

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> o[i] >> d[i];

    // 顺时针
    for (int i = 1; i <= n; i++)
        s[i] = s[i + n] = o[i] - d[i];
    for (int i = 1; i <= 2 * n; i++)
        s[i] += s[i - 1];

    int hh = 0, tt = -1;
    for (int i = 2 * n; i; i--)
    {
        if (hh <= tt && q[hh] > i + n - 1)
            hh++;
        while (hh <= tt && s[q[tt]] >= s[i])
            tt--;
        q[++tt] = i;
        if (i <= n && s[q[hh]] >= s[i - 1])
            ans[i] = true;
    }

    // 逆时针
    d[0] = d[n];
    hh = 0, tt = -1;
    for (int i = 1; i <= n; i++)
        s[i] = s[i + n] = o[i] - d[i - 1];
    for (int i = 2 * n; i; i--)
        s[i] += s[i + 1];
    for (int i = 1; i <= 2 * n; i++)
    {
        if (hh <= tt && q[hh] < i - n - 1)
            hh++;
        while (hh <= tt && s[q[tt]] >= s[i])
            tt--;
        q[++tt] = i;
        if (i > n && s[q[hh]] >= s[i + 1])
            ans[i - n] = true;
    }

    for (int i = 1; i <= n; i++)
        if (ans[i])
            cout << "TAK" << endl;
        else
            cout << "NIE" << endl;

    return 0;
}