// acwing 884 高斯消元解异或线性方程组
/*
    异或 = 不进位的加法
    1.消成上三角矩阵
        1.1.枚举列
        1.2.找每一行中绝对值最大的那一行
        1.3.将该行换到第一行
        1.4.将该行第一列的下面消为0
    2.判断解的情况
        r(n)=r(n')=n  唯一解
        r(n)<r(n')    无解
        r(n)=r(n')<n  无穷多解
*/
#include <iostream>
using namespace std;
const int N = 110;
int a[N][N];
int n;

int gauss()
{
    int r, c;
    // 1.枚举每一列
    for (r = 0, c = 0; c < n; c++)
    {
        // 2.找到当前列，值为1的那一行
        int t = r;
        for (int i = r; i < n; i++)
            if (a[i][c])
            {
                t = i;
                break;
            }
        if (!a[t][c])
            continue;

        // 3.将该行换到第一行
        for (int i = c; i <= n; i++)
            swap(a[t][i], a[r][i]);

        // 4.将该行下边的变为0
        for (int i = t + 1; i < n; i++)
            if (a[i][c])
                for (int j = c; j <= n; j++)
                    a[i][j] = a[i][j] ^ a[r][j];
        
        r++;
    }
    // 判断解的情况
    if (r < n)
    {
        for (int i = r; i < n; i++)
            if (a[i][n] == 1)
                return 2; // 无解
        return 1;         // 无穷多解
    }

    for (int i = n - 1; i >= 0; i--)
        for (int j = i + 1; j < n; j++)
            a[i][n] = a[i][n] ^ (a[i][j] * a[j][n]);

    return 0;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= n; j++)
            cin >> a[i][j];

    int res = gauss();
    if (!res)
        for (int i = 0; i < n; i++)
            cout << a[i][n] << endl;
    else if (res == 1)
        puts("Multiple sets of solutions");
    else if (res == 2)
        puts("No solution");

    return 0;
}