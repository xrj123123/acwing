// acwing 1014 登山
/*
    求出某一点的最长上升子序列和最长下降子序列，相加最大值即为结果
*/

#include <iostream>
using namespace std;

const int N = 1010;
int h[N], l[N], r[N];
int n;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> h[i];
    
    for (int i = 1; i <= n; i++)
    {
        l[i] = 1;
        for (int j = 1; j < i; j++)
            if (h[i] > h[j])
                l[i] = max(l[i], l[j] + 1);
    }

    for (int i = n; i > 0; i--)
    {
        r[i] = 0;
        for (int j = n; j > i; j--)
            if (h[i] > h[j])
                r[i] = max(r[i], r[j] + 1);
    }

    int res = 0;
    for (int i = 1; i <= n; i++)
        res = max(res, r[i] + l[i]);
    
    cout << res << endl;
    return 0;
}