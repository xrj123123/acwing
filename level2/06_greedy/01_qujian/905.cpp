// acwing 905 区间选点
/*
    1.将区间按右端点从小到大排序
    2.依次枚举每个区间，如果当前区间被那个点覆盖，则pass
      否则，res++
*/
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int n;

struct Range
{
    int l, r;
    bool operator<(const Range &W) const
    {
        return r < W.r;
    }
} range[N];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;
        range[i] = {l, r};
    }

    sort(range, range + n);

    int res = 0, ed = -1e9 - 10;
    for (int i = 0; i < n; i++)
    {
        if (range[i].l > ed)
        {
            ed = range[i].r;
            res++;
        }
    }

    cout << res << endl;

    return 0;
}