// acwing 8 二维费用背包问题

#include <iostream>
using namespace std;

const int N = 1010;
int f[110][110];
int v[N], m[N], w[N];
int K, V, M;

int main()
{
    cin >> K >> V >> M;

    for (int i = 0; i < K; i++)
        cin >> v[i] >> m[i] >> w[i];
    
    for (int i = 0; i < K; i++)
        for (int j = V; j >= v[i]; j--)
            for (int k = M; k >= m[i]; k--)
                f[j][k] = max(f[j][k], f[j - v[i]][k - m[i]] + w[i]);
    
    cout << f[V][M] << endl;

    return 0;
}