// acwing 1085 不要62
/*
    数位dp
    n = abcdefg，在第一位取值有两种情况：1、取[0,a-1],该位不能取4，last表示上一位数字取值，last取6，该位不能取2
                                       2、取a，a如果等于4或者last取6该位取2直接break
    左子树的求法
    状态表示: f[i][j]表示一共有i位，当前最高位取j时合法方案数
    状态计算: f[i][j] = ∑f[i-1][k] (k!=4 && j!=6||k!=2)
*/
#include <iostream>
#include <vector>
using namespace std;
const int N = 10;
int f[N][10];

void init()
{
    for (int i = 0; i < 10; i++) 
        if (i != 4)
            f[1][i] = 1;
    for (int i = 2; i < N; i++)
        for (int j = 0; j <= 9; j++)
        {
            if (j == 4) continue;
            for (int k = 0; k <= 9; k++)
            {
                if (k == 4 || j == 6 && k == 2) continue;
                f[i][j] += f[i - 1][k];
            }
        }
}

int dp(int n)
{
    if (!n) return  1;
    int res = 0;
    int last = 0;   // last表示上一位数字
    vector<int> nums;
    while (n) nums.push_back(n % 10), n /= 10;

    for (int i = nums.size() - 1; i >= 0; i--)
    {
        int x = nums[i];
        for (int j = 0; j < x; j++)
        {
            if (j == 4 || last == 6 && j == 2) continue;
            res += f[i + 1][j];
        }
        if (x == 4 || last == 6 && x == 2) break;
        last = x;
        if (!i) res++;
    }
    return res;
}

int main()
{
    int n, m;
    init();
    while (cin >> n >> m, n || m)
    {
        cout << dp(m) - dp(n - 1) << endl;
    }
}