// 逆序对的数量
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
int n;
LL res;
int q[N], tmp[N];

void merge_sort(int q[], int l, int r)
{
    if (l >= r)
        return;

    int mid = l + r >> 1;

    merge_sort(q, l, mid);
    merge_sort(q, mid + 1, r);

    // 归并
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (q[i] <= q[j])
            tmp[k++] = q[i++];
        else
        {
            tmp[k++] = q[j++];
            res += mid - i + 1;
        }
    }

    // 扫尾
    while (i <= mid)
        tmp[k++] = q[i++];
    while (j <= r)
        tmp[k++] = q[j++];

    // 物归原主
    for (i = l, j = 0; i <= r; i++, j++)
        q[i] = tmp[j];
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &q[i]);

    merge_sort(q, 0, n - 1);
    cout << res << endl;

    return 0;
}
