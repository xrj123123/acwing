// acwing 291   蒙德里安的梦想
/*
    先把横着的摆好，剩余的地方摆竖着的，因此总方案数 = 摆横着放的方案数

    状态表示：
        f[i][j]表示摆到第i列了(前i-1列摆好了)，从第i-1列伸出来的格子表示当前状态j，伸出来用1表示，没伸出来0表示
    状态计算：
        从i-1列转移过来，合法的情况是，(i-1&i)==0，i-1列的状态和i列的状态不能冲突，第x行，i-2列伸出来了，那么i-1就不能伸出来
        并且i-1列和i列的状态必须 不能有奇数个连续的0，否则无法用竖着的格子摆
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 12, M = 1 << N;
long long f[N][M]; // f[i][j]表示摆到第i列，当前状态为j
bool st[M];  // st[i]表示第i中状态是否合法
int n, m;

int main()
{
    while (cin >> n >> m, n || m)
    {
        // 先预处理st,如果存在奇数个0就是false
        for (int i = 0; i < 1 << n; i++)
        {
            st[i] = true;
            int cnt = 0; // 连续0的个数
            for (int j = 0; j < n; j++)
            {
                if (i >> j & 1) // i的第j位为1
                {
                    if (cnt & 1)    // 奇数个0
                    {
                        st[i] = false;
                        break;
                    }
                }
                else
                    cnt++;
            }
            if (cnt & 1)
                    st[i] = false;
        }

        memset(f, 0, sizeof f);
        f[0][0] = 1; // 摆到第0列了，当前状态为0，方案数为1

        for (int i = 1; i <= m; i++)             // 每一列
            for (int j = 0; j < 1 << n; j++)     // 当前状态j
                for (int k = 0; k < 1 << n; k++) // 前一列状态k
                    if ((j & k) == 0 && st[j | k])    // i列和i-1列不冲突 并且i-1列过来的和i列出去的有连续偶数个0
                        f[i][j] += f[i - 1][k];

        cout << f[m][0] << endl;
    }

    return 0;
}