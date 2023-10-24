// acwing 482 合唱队形
/*
    计算出先上升后下降的最长序列长度，总数减去该长度即为出列的人数
*/
#include <iostream>
using namespace std;

const int N = 110;
int h[N], l[N], r[N];
int n;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &h[i]);
    
    for (int i = 1; i <= n; i++)
    {
        l[i] = 1;
        for (int j = 1; j < i; j++)
            if (h[i] > h[j])
                l[i] = max(l[i], l[j] + 1);
    }

    for (int i = n; i >= 1; i--)
    {
        for (int j = n; j > i; j--)
            if (h[i] > h[j])
                r[i] = max(r[i], r[j] + 1);
    }

    int res = 0;
    for (int i = 1; i <= n; i++)
        res = max(res, l[i] + r[i]);
    
    cout << n - res << endl;

    return 0;   
}