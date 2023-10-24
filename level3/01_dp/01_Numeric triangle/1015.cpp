// acwing 1015 摘花生
/*
    f[i][j]表示走到(i,j)时的最大值
    f[i][j] = max(f[i - 1][j], f[i][j - 1]) + map[i][j]
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 110;
int map[N][N];
int f[N][N];
int t, r, c;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> r >> c;
        memset(f, 0, sizeof f);
        memset(map, 0, sizeof map);
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                cin >> map[i][j];

        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                f[i][j] = max(f[i - 1][j], f[i][j - 1]) + map[i][j];
        cout << f[r][c] << endl;
    }

    return 0;
}