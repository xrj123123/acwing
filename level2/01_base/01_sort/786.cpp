// 第k个数
/*#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int n, k;
int q[N];

void quick_sort(int q[], int l, int r)
{
    if (l >= r)
        return;

    int i = l - 1, j = r + 1, x = q[l + r >> 1];

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
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &q[i]);

    quick_sort(q, 0, n - 1);
    printf("%d\n", q[k - 1]);

    return 0;
} */

// 快速选择排序
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int n, k;
int q[N];

int quick_sort(int l, int r, int k)
{
    if (l == r)
        return q[l];

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

    int sl = j - l + 1; // 小于等于x的个数

    if (sl >= k)
        return quick_sort(l, j, k);

    return quick_sort(j + 1, r, k - sl);
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> q[i];

    cout << quick_sort(0, n - 1, k) << endl;

    return 0;
}