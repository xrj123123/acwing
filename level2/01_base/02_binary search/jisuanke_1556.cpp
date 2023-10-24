// 计蒜客 1556 二分查找（六）
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int n, m;
int q[N], tmp[N];

void merge_sort(int q[], int l, int r)
{
    if (l >= r)
        return;
    int mid = l + r >> 1;
    merge_sort(q, l, mid);
    merge_sort(q, mid + 1, r);

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (q[i] < q[j])
            tmp[k++] = q[i++];
        else
            tmp[k++] = q[j++];
    }

    while (i <= mid)
        tmp[k++] = q[i++];
    while (j <= r)
        tmp[k++] = q[j++];

    for (int i = l, j = 0; i <= r; i++, j++)
        q[i] = tmp[j];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &q[i]);
    merge_sort(q, 0, n - 1);

    int x;
    // 小于x的最大值
    while (m--)
    {
        scanf("%d", &x);
        if (q[0] >= x)
            printf("%d\n", -1);
        else
        {
            int l = 0, r = n - 1;
            while (l < r)
            {
                int mid = l + r + 1 >> 1;
                if (q[mid] < x)
                    l = mid;
                else
                    r = mid - 1;
            }
            printf("%d\n", q[l]);
        }
    }

    return 0;
}