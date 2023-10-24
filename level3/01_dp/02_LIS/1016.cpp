// acwing 1016 最大上升子序列和

#include <iostream>
using namespace std;

const int N = 1010;
int a[N], f[N];
int n;

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        f[i] = a[i];
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[i] > a[j])
                f[i] = max(f[i], f[j] + a[i]);
    
    int res = 0;
    for (int i = 0; i < n; i++)
        res = max(res, f[i]);
    
    cout << res << endl;
    return 0;
}