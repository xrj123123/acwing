// acwing 1017 怪盗基德的滑翔翼 
/*
    双向LIS
*/
#include <iostream>
using namespace std;

const int N = 110;
int k, n, a[N], f[N];

int main()
{
    scanf("%d", &k);
    while (k--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        
        int res = 0;
        // 正向
        for (int i = 1; i <= n; i++)
        {
            f[i] = 1;
            for (int j = 1; j < i; j++)
                if (a[i] > a[j])
                    f[i] = max(f[i], f[j] + 1);
            res = max(res, f[i]);
        }

        // 反向
        for (int i = n; i >= 1; i--)
        {
            f[i] = 1;
            for (int j = n; j > i; j--)
                if (a[i] >= a[j])
                    f[i] = max(f[i], f[j] + 1);
            res = max(res, f[i]);
        }
            
        cout << res << endl;    
    }

    return 0;
}