// acwing 1019 庆功会
#include <iostream>
using namespace std;

const int N = 6010, M = 2010;
int f[N];
int v[M], w[M];
int n, m, cnt;

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int a, b, c;    // 价格、价值、数量
        cin >> a >> b >> c;
        for (int j = 1; j <= c; j *= 2)
        {
            v[cnt] = j * a;
            w[cnt++] = j * b;
            c -= j;
        }
        if (c)
        {
            v[cnt] = c * a;
            w[cnt++] = c * b;
        }    
    }



    for (int i = 0; i < cnt; i++)
        for (int j = m; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);

    cout << f[m] << endl;

    return 0;
}