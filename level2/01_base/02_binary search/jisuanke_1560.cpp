// 计蒜客 1560 二分查找（一）
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100010;
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
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &x);
        int l = 0, r = n - 1, flag = 0;
        while (l <= r)
        {
            if (q[r] < x || q[l] > x)
                break;
            int mid = l + r >> 1;
            if (q[mid] == x)
            {
                printf("%s\n", "YES");
                flag = 1;
                break;
            }
            else if (q[mid] > x)
                r = mid - 1;
            else
                l = mid + 1;
        }
        if (flag == 0)
            printf("%s\n", "NO");
    }

    return 0;
}