// acwing 524 愤怒的小鸟
/*
    dfs方法
    void(int state, int cnt)    // state是当前那些小猪被覆盖,cnt是用的曲线数
    {
        if (state已经包含所有小猪) return 0;
        枚举一个没有被覆盖的小猪x
            枚举所有能覆盖x的曲线
                更新state -> new_state
                dfs(new_state, cnt + 1);
    }
    转为dp就是将每个状态存下来，避免重复计算
    状态表示：f[state]表示覆盖小猪状态为state时需要的曲线数的最小值
    状态计算：任取没有被state覆盖的小猪x，枚举所有可以覆盖x的曲线，path[x][j] (path[x][j]表示经过点x和j的曲线可以覆盖的小猪)
            new_state = state | path[x][j]
            f[new_state] = min(f[new_state], f[state] + 1);

    y = ax^2 + bx + c
    抛物线开口向下，且过原点, 所以a < 0, c = 0
    用两点确定抛物线,(x1, y1),(x2, y2)  (x1 != x2)
    a * x1^2 + b * x1 = y1        a = (y1 / x1 - y2 / x2) / (x1 - x2)
    a * x2^2 + b * x2 = y2        b = y1 / x1 -a * x1
*/
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
#define x first
#define y second
typedef pair<double, double> PDD;

const int N = 18, M = 1 << 18;
const double eps = 1e-6;
PDD q[N];   // 存储小猪坐标
int path[N][N]; // path[i][j]表示经过i和j的小猪的抛物线可以覆盖的状态
int f[M];
int n, m;

int cmp(double x1, double x2)
{
    if (fabs(x1 - x2) < eps)
        return 0;
    if (x1 < x2)    
        return -1;
    return 1;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        for (int i = 0; i < n; i++)
            cin >> q[i].x >> q[i].y;
        memset(path, 0, sizeof path);

        // 预处理path
        for (int i = 0; i < n; i++)
        {
            path[i][i] = 1 << i;
            for (int j = 0; j < n; j++)
            {
                double x1 = q[i].x, y1 = q[i].y;
                double x2 = q[j].x, y2 = q[j].y;
                if (!cmp(x1, x2)) continue;
                double a = (y1 / x1 - y2 / x2) / (x1 - x2);
                double b =  y1 / x1 - a * x1;
                if (cmp(a, 0) >= 0) continue;
                int state = 0;
                for (int k = 0; k < n; k++)
                {
                    double x = q[k].x, y = q[k].y;
                    if (!cmp(a * x * x + b * x, y))
                        state += 1 << k;
                }
                path[i][j] = state;
            }
        }

        memset(f, 0x3f, sizeof f);
        f[0] = 0;
        for (int i = 0; i + 1 < 1 << n; i++)    // 枚举所有状态
        {
            int x;
            // 这里本应是枚举所有未覆盖的小猪，但是时间复杂度会增加n倍，优化后，每次找出第一只未被更新的小猪即可
            // 这样做，可能只有最终答案是最优解，中间状态只有部分是最优
            // 可以这么做的原因是i从0开始，每次更新时, i | path[j][k]一定大于i，从0开始更新的状态，最后一定会走到
            // 然后继续更新下一个状态，类似最短路
            for (int j = 0; j < n; j++) // 找出任意一个当前状态没有覆盖的小猪x
                if (!(i >> j & 1))
                {
                    x = j;
                    break;
                }

            for (int j = 0; j < n; j++)
                f[i | path[x][j]] = min(f[i | path[x][j]], f[i] + 1);
        }
        cout << f[(1 << n) - 1] << endl;
    }
    return 0;
}