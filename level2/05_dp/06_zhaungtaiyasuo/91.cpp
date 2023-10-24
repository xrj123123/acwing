// acwing 91 最短Hamilton路径
/*
    状态表示：
        f[i][j] 表示从0走到j，走的路径为i(二进制表示)，路径最小值

    状态计算：
        f[i][j] 从前一个点转移过来
        假设从第k个点转移过来，f[i][j] = min(f[i][j], f[i - {j}][k] + w[k][j])，从0走到k，那么此时状态不包括j这个点
 */
#include <iostream>
#include <cstring>
using namespace std;
const int N = 20, M = 1 << N;
int w[N][N];
int f[M][N];
int n;

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> w[i][j];
    
    memset(f, 0x3f, sizeof f);
    f[1][0] = 0;    // 从0走到0，当前状态为1，距离为0

    for(int i = 0; i < 1 << n; i++)
        for(int j = 0; j < n; j++)  
            if((i >> j) & 1)    // 当前状态为i，走到了j，那么i的状态中j必须走过了
                for(int k = 0; k < n; k++)  // 从k转移过来
                    if(((i - (1 << j)) >> k) & 1)
                        f[i][j] = min(f[i][j], f[i- (1 << j)][k] + w[k][j]);

    cout << f[(1 << n) - 1][n - 1] << endl;

    return 0;
}

