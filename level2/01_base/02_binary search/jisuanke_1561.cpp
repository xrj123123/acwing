// 计蒜客 1561 二分查找（二）
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int n, m;
int q[N];

void quick_sort(int q[], int l, int r)
{
    if (l >= r)
        return;
    int x = q[l + r >> 1], i = l - 1, j = r + 1;
    while (i < j)
    {
        do
            i++;
        while (q[i] < x);
        do
            j--;
        while (q[j] > x);
        if (i < j)
            swap(q[i], q[j]);
    }
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &q[i]);
    quick_sort(q, 0, n - 1);

    int x;
    while (m--)
    {
        scanf("%d", &x);
        int l = 0, r = n - 1;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (q[mid] >= x)
                r = mid;
            else
                l = mid + 1;
        }
        if (q[l] >= x)
            printf("%d\n", q[l]);
        else
            printf("%d\n", -1);
    }

    return 0;
}