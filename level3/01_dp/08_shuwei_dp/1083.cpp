// acwing 1083 Windy数
/*
    数位dp
    因为这道题不能有前导0，因此对于n = abcdefg，在第一位a划分时，左子树只能取[1,a-1]，不能取0，
    而从第二位开始，后边的左子树就可以取0。
    在第一位计算时不能有前导0，因此算的是位数为n的情况，但是有前导0的情况，即位数小于n时也需要加进去
    左子树计算方法：
    状态表示: f[i][j]表示一共有i位，最高位为j时的方案数
    状态计算: f[i][j] = ∑f[i-1][k] (j+2 <= k <= 9, 0 <= k <= j-2)
*/
#include <iostream>
#include <vector>
using namespace std;
const int N = 11;
int f[N][N];
int A, B;

void init()
{
    for (int i = 0; i <= 9; i++) f[1][i] = 1;
    for (int i = 2; i < N; i++)
        for (int j = 0; j <= 9; j++)
            for (int k = 0; k <= 9; k++)
                if (abs(j - k) >= 2)
                    f[i][j] += f[i - 1][k];
}

int dp(int n)
{
    if (!n)
        return 0;
    int res = 0;
    int last = -2;  // 因为第一位数字可以随便填
    vector<int> nums;
    while (n)
    {
        nums.push_back(n % 10);
        n /= 10;
    }

    for (int i = nums.size() - 1; i >= 0; i--)
    {
        int x = nums[i];
        for (int j = i == nums.size() - 1; j < x; j++)
        {
            if (abs(j - last) >= 2)
                res += f[i + 1][j];
        }
        if (abs(last - x) < 2) break;
        last = x;
        if (!i) res++;
    }
    
    // 有前导0，即位数小于nums.size(),上边统计的都是位数等于nums.size()的
    for (int i = 1; i < nums.size(); i++)
        for (int j = 1; j <= 9; j++)
            res += f[i][j];
    return res;
}

int main()
{
    cin >> A >> B;

    init();
    cout << dp(B) - dp(A - 1) << endl;

    return 0;
}