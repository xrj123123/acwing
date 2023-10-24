// acwing 803 区间合并
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> PII;
vector<PII> segs;
int n;

void merge(vector<PII> &segs)
{
    vector<PII> res;
    sort(segs.begin(), segs.end()); // pair排序默认先排第一个
    int l = -2e9, r = -2e9;
    for (auto seg : segs)
    {
        if (seg.first > r)
        {
            if (r != -2e9)
                res.push_back(seg);
            l = seg.first;
            r = seg.second;
        }
        else
            r = max(r, seg.second);
    }
    if (l != -2e9)
        res.push_back({l, r});
    segs = res;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;
        segs.push_back({l, r});
    }
    merge(segs);
    cout << segs.size() << endl;

    return 0;
}
