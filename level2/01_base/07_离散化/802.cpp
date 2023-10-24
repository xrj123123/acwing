// acwing 802 区间和   离散化做法  离散化是一种特殊的hash，他要保证数组有序
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 3e5 + 10;
int n, m;
int a[N], s[N];
typedef pair<int, int> PII;
vector<PII> add, query; // 原来保存操作输入的值
vector<int> alls;       // 离散化原数组下标，和左右区间值

// 找到>=x的最小值，x插入该位置
int find(int x)
{
    int l = 0, r = alls.size() - 1;
  
    while (l < r)
    {
        int mid = l + r >> 1;
        if (alls[mid] >= x)
            r = mid;
        else
            l = mid + 1;
    }
    return r + 1; // 加1是因为，让下标在1-n之间，方便求前缀和
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int x, c;
        cin >> x >> c; // 在坐标为x的地方加上c
        alls.push_back(x);
        add.push_back({x, c});
    }
    for (int i = 0; i < m; i++)
    {
        int l, r;
        cin >> l >> r;
        alls.push_back(l);
        alls.push_back(r);
        query.push_back({l, r});
    }
    sort(alls.begin(), alls.end());
    // unique(alls.begin(),alls.end() 将不重复的元素放前边，返回不重复元素的后一个下标
    // erase(l,r)   删除从l到r的元素
    alls.erase(unique(alls.begin(), alls.end()), alls.end()); // 去重
    for (auto item : add)                                     // 先对添加里的元素记性映射
    {
        int x = find(item.first); // 找到映射值，然后+c
        a[x] += item.second;
    }
    for (int i = 1; i <= alls.size(); i++)
    {
        s[i] = s[i - 1] + a[i]; // 前缀和
    }
    for (auto item : query)
    {
        int l = find(item.first);
        int r = find(item.second);
        cout << s[r] - s[l - 1] << endl;
    }

    return 0;
}
