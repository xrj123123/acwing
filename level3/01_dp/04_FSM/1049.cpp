// acwing 1049 大盗阿福
/*
    状态表示：f[i]表示前i家店铺可获得的最大价值
    状态计算：不选第i家店铺，f[i-1]
             选第i家店铺，f[i-2] + a[i]
             f[i] = max(f[i-1], f[i-2]+a[i])
*//*
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5 + 10;
int f[N], a[N];
int T;

int main()
{
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];

        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; i++)
            f[i] = max(f[i - 1], f[i - 2] + a[i]);

        cout << f[n] << endl;
    }
    return 0;
}*/

/*
    状态机模型
    f[i][0]表示在第i个商铺的时候不选i，f[i][1]表示在第i个商铺时选i
    状态机可以表示为：0 -> 0
                    0 -> 1
                    1 -> 0
    f[i][0] = max(f[i-1][0], f[i-1][1]);
    f[i][1] = f[i-1][0] + a[i];
    初始状态只能转为0状态
    因此f[0][0] = 0, f[0][1] = -INF
*/
#include <iostream>
using namespace std;

#define INF 0x3f3f3f3f
const int N = 1e5 + 10;

int f[N][2], a[N];
int T;

int main()
{
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        f[0][0] = 0;
        f[0][1] = -INF;
        for (int i = 1; i <= n; i++)
        {
            f[i][0] = max(f[i - 1][0], f[i - 1][1]);
            f[i][1] = f[i - 1][0] + a[i];
        }
        int res = max(f[n][0], f[n][1]);
        cout << res << endl;
    }
    return 0;
}