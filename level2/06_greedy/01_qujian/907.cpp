// acwing 907 区间覆盖
/*
    1.将所有区间按左端点从小到大排序
        初试化start为线段区间左端点
    2.每次找到一个覆盖(左端点小于start)start，并且右端点最大的区间
        更新右端点为start
*/
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int st, ed, n;

struct Range
{
    int l, r;
    bool operator<(const Range &W) const
    {
        return l < W.l;
    }
} range[N];

int main()
{
    cin >> st >> ed;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;
        range[i] = {l, r};
    }

    sort(range, range + n);

    int res = 0;
    bool flag = false;

    for (int i = 0; i < n; i++)
    {
        // 双指针遍历
        int j = i, r = -2e9;
        while (j < n && range[j].l <= st)
        {
            r = max(r, range[j].r);
            j++;
        }

        if (r < st) // 如果当前最大的也小于st，说明无法覆盖
            break;

        res++;
 
        if (r >= ed) // r大于ed，直接退出
        {
            flag = true;
            break;
        }

        st = r;    // 更新st
        i = j - 1; // 要让i从j开始执行，因为还要执行i++,所以先j-1
    }

    if (!flag)
        res = -1;
    cout << res << endl;
    return 0;
}