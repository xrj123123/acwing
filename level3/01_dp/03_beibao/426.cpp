// acwing 426 开心的金明
#include <iostream>
using namespace std;

const int N = 30, M = 30010;
int f[M];
int n, m;

int main()
{
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
    {
        int v, p, w;
        cin >> v >> p;
        w = v * p;
        for (int j = m; j >= v; j--)
            f[j] = max(f[j], f[j - v] + w);
    }

    cout << f[m] << endl;
    return 0;
}