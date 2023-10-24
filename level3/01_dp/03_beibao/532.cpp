// acwing 532 货币系统
/*
    1. a数组的数都可以被b数组表示出来
    2. b中的数是a的子集
       证：假设bi ∉ a，bi = a1 + a2 + a3, 
                      a1 = b1 + b2 + b3
                      a2 = b2 + b3
                      a3 = b3 + b4
         则bi = b1 + 2 * b2 + 3 * b3 + b4,bi可由b1...b4表示，因此bi不需要存在于b中 
    3. b1、b2、...bm一定不能被其他bi表示出来(线性无关)

    将a数组从小到大排序，依次判断ai是否能被前边的数字表示出来，如果可以，那么一定不选ai，如果不可以，那么一定选ai
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 110, M = 25010;
int a[N], f[M];
int T;

int main()
{
    cin >> T;
    while (T--)
    {
        int n; 
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> a[i];

        sort(a, a + n);
        int m = a[n - 1];
        memset(f, 0, sizeof f);
        f[0] = 1;

        int res = 0;
        for (int i = 0; i < n; i++)
        {
            if (!f[a[i]])   res++;
            for (int j = a[i]; j <= m; j++)
                f[j] += f[j - a[i]];
        }

        cout << res << endl;
    }

    return 0;
}