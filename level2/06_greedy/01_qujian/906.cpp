// acwing 906 区间分组
/*
    1.将所有区间按左端点从小到大排序
    2.从前到后处理每个区间
        判断能否将其放到某个现有的组中：L[i] > max_r
            每次判断的就是最小的max_r是否小于L[i]，可以小根堆实现
            1.如果不存在这样的组，则开新的组，将其放进去
            2.如果存在(随便挑一个放进去即可)，将其放进去，并更新当前的max_r

*/
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 1e5 + 10;
int n;

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
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;
        range[i] = {l, r};
    }

    sort(range, range + n);

    // 小根堆
    priority_queue<int, vector<int>, greater<int>> heap;

    for (int i = 0; i < n; i++)
    {
        auto t = range[i];
        if (heap.empty() || heap.top() >= t.l) // 堆为空或者当前区间的左端点小于堆顶右端点
            heap.push(t.r);
        else // 存在可以加入的组
        {
            heap.pop();
            heap.push(t.r);
        }
    }

    cout << heap.size() << endl;

    return 0;
}