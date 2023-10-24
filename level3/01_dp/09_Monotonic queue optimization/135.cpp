// acwing 135 最大子序和
/*
    单调队列
    长度为n的序列中，找出一段长度不超过m的连续子序列，让其和最大
    首先需要枚举终点，在[1, n]之间
    假设当前终点为k，要求出以k为终点且长度不超过m的连续子序列的最大值
    用s数组表示前缀和，即让s[k]-s[k-j], (1<=j<=m) 最大，也就是让s[k-j]最小，转为单调队列来求区间最小值
*/
#include <iostream>
using namespace std;
const int N = 300010;
int s[N], q[N];
int hh = 0, tt = 0; // hh是队头，tt是队尾
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        s[i] = s[i - 1] + x;
    }

    int res = -0x3f3f3f3f;
    // 队头元素为s[0] = 0
    for (int i = 1; i <= n; i++)
    {
        if (q[hh] < i - m)  // 因为是前缀和，所以这里长度+1
            hh++;
        res = max(res, s[i] - s[q[hh]]);
        while (hh <= tt && s[q[tt]] >= s[i])
            tt--;
        q[++tt] = i;
    }

    cout << res << endl;

    return 0;
}