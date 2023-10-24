// acwing 789 数的范围
/*
整数二分模板

1. 大于等于x的最小值
while (l < r)
{
    int mid = l + r >> 1;
    if (check(mid))
        r = mid;
    else
        l = mid + 1;
}
2. 小于等于x的最大值
while (l < r)
{
    int mid = l + r + 1 >> 1;
    if (check(mid))
        l = mid;
    else
        r = mid - 1;
}
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int n, x, m;
int a[N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &x);

        // 找>=q的最小值
        int l = 0, r = n - 1;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (a[mid] >= x)
                r = mid;
            else
                l = mid + 1;
        }
        if (a[l] != x)
            cout << -1 << " " << -1 << endl;
        else
        {
            cout << l << " ";
            // 找<=x的最大值
            int l = 0, r = n - 1;
            while (l < r)
            {
                int mid = l + r + 1 >> 1;
                if (a[mid] <= x)
                    l = mid;
                else
                    r = mid - 1;
            }
            cout << l << endl;
        }
    }

    return 0;
}
