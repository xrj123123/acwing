// acwing 154 滑动窗口      
/*
    单调队列
    单调队列解决的问题一般是求在一个窗口内的最大值最小值问题
*/
#include <iostream>
using namespace std;
const int N = 1e6 + 10;
int q[N], a[N];
int hh = 0, tt = -1; // hh为队尾，tt为队头
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < n; i++)
    {
        // 队列中存的是下标
        // 如果队列中元素超出k，删除,每次只会进一个，所以if就可以
        if (hh <= tt && i - k + 1 > q[hh])
            hh++;
        // 队头元素大于等于要入队的，弹出
        while (hh <= tt && a[q[tt]] >= a[i])
            tt--;
        q[++tt] = i;
        if (i >= k - 1)
            printf("%d ", a[q[hh]]);
    }
    puts("");

    hh = 0, tt = -1;
    for (int i = 0; i < n; i++)
    {
        // 队列中存的是下标
        // 如果队列中元素超出k，删除,每次只会进一个，所以if就可以
        if (hh <= tt && i - k + 1 > q[hh])
            hh++;
        // 队头元素小于等于于要入队的，弹出
        while (hh <= tt && a[q[tt]] <= a[i])
            tt--;
        q[++tt] = i;
        if (i >= k - 1)
            printf("%d ", a[q[hh]]);
    }
    puts("");

    return 0;
}
