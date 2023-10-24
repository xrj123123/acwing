// acwing 1010 拦截导弹
/*
    贪心 + LIS
    贪心流程：从前到后扫描每个数，对于每个数
        case1: 如果现有的子序列的结尾都小于当前数，则创建新的序列
        case2: 将当前数放在序列结尾大于等于该数的最小的序列的后边
    因此该解法与最长上升子序列2一模一样
*/
#include <iostream>
using namespace std;

const int N= 1010;
int h[N], f[N], q[N];
int n;

// 找到大于等于x的最小值
int find(int l, int r, int x)
{
    while (l < r)
    {
        int mid = l + r >> 1;
        if (q[mid] >= x)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int main()
{
    while (cin >> h[n]) n++;
    
    // 求最多拦截的导弹数
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        f[i] = 1;
        for (int j = 0; j < i; j++)
            if (h[i] <= h[j])
                f[i] = max(f[i], f[j] + 1);
        res = max(res, f[i]);
    }
    cout << res << endl;

    // 求最少需要的系统数
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (cnt == 0 || h[i] > q[cnt - 1])
            q[cnt++] = h[i];
        else
        {
            int idx = find(0, cnt, h[i]);
            q[idx] = h[i];
        }
    }
    
    cout << cnt << endl;

    return 0;
}