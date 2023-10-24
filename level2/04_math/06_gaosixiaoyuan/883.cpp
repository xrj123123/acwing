// acwing 883 高斯消元解线性方程组
/*
    解多元线性方程组：
        初等行列变换
        1.把某一行乘一个非零的数  2.交换某两行    3.把某行的若干倍加到某一行去
    可以用高斯消元将其转为上三角矩阵
        1. r(系数)=r(增广)=n    唯一解
        2. r(系数)<r(增广)      无解
        3. r(系数)=r(增广)<n    无穷解

    高斯消元法:
        枚举每一列
            1.找到绝对值最大数的那一行
            2.将该行换到最上面
            3.将该行第一个数变为1
            4.将下面所有行的第c列消成0
*/
#include <iostream>
#include <cmath>
using namespace std;
const int N = 110;
const double eps = 1e-6;
double a[N][N];
int n;

int gauss()
{
    int r, c;                      // r为行，c为列
    for (r = 0, c = 0; c < n; c++) // 枚举每一列
    {
        // 1.找到绝对值最大数的那一行
        int t = r;
        for (int i = r; i < n; i++)
        {
            if (fabs(a[i][c]) > fabs(a[t][c]))
                t = i;
        }

        if (fabs(a[t][c]) < eps) // 如果找到该列最大的数为0，则continue
            continue;

        // 2.将该行换到最上面
        for (int i = c; i <= n; i++)
            swap(a[t][i], a[r][i]);

        // 3.将该行第一个数变为1
        for (int i = n; i >= c; i--)
            a[r][i] /= a[r][c];

        // 4.将下面所有行的第c列消成0
        for (int i = r + 1; i < n; i++)
            if (fabs(a[i][c]) > eps)
                for (int j = n; j >= c; j--)
                    a[i][j] -= a[r][j] * a[i][c];
        r++;
    }

    if (r < n) // 只要r-n行的最后一位数不为0，就无解，否则无穷多解
    {
        for (int i = r; i < n; i++)
            if (fabs(a[i][n]) > eps)
                return 2; // 无解
        return 1;         // 无穷多借
    }

    // 求出对应的解
    for (int i = n - 1; i >= 0; i--)
        for (int j = i + 1; j < n; j++)
            a[i][n] -= a[i][j] * a[j][n];

    return 0; // 唯一解
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= n; j++)
            cin >> a[i][j];

    int t = gauss();
    if (!t)
    {
        for (int i = 0; i < n; i++)
        {
            if (fabs(a[i][n]) < eps)
                printf("%.2lf\n", 0.0); // 不能写0
            else
                printf("%.2lf\n", a[i][n]);
        }
    }
    else if (t == 1)
        puts("Infinite group solutions");
    else if (t == 2)
        puts("No solution");
    return 0;
}