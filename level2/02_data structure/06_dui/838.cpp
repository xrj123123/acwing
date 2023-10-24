// acwing 838 堆排序
// 手写堆的基本操作；STL的堆只有前三个功能      堆是一个完全二叉树，小根堆：每一个点都小于等于左右儿子
// 1.插入一个数  2.求集合当中的最小值  3.删除最小值 4.删除任意一个元素  5.修改任意一个元素

// 1.h[++size]=x; up[size];     2.h[1];     3.h[1]=h[size];  down(1);
// 4.h[k]=h[size];  down(k); up(k);     5.h[k]=x; down(k);  up(k);

#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int h[N], size; // h表示堆，size表示堆的大小

// 将元素h[u]向下调整，因为是最小堆，所以u应该小于等于他的左右儿子
void down(int u)
{
    int t = u;
    if (2 * u <= size && h[t] > h[2 * u])
        t = 2 * u;
    if (2 * u + 1 <= size && h[t] > h[2 * u + 1])
        t = 2 * u + 1;
    if (u != t)
    {
        swap(h[t], h[u]);
        down(t);
    }
}

// 将元素h[u]向上调整
void up(int u)
{
    while (u / 2 && h[u / 2] > h[u])
    {
        swap(h[u / 2], h[u]);
        u /= 2;
    }
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &h[i]);
    size = n;

    // 插入完之后，需要调整为最小堆
    // down时间复杂度为logn,全部down的话复杂度为nlogn,从n/2(最后一个非叶子结点)开始down,时间复杂度小于n
    for (int i = n / 2; i; i--)
        down(i);

    while (m--)
    {
        printf("%d ", h[1]);
        h[1] = h[size];
        size--;
        down(1);
    }
    puts("");

    return 0;
}