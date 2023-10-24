// acwing 338 计数问题
/*
n=abc d efg 此时求d位为x 的数字个数
1.000-abc-1  x
  1.1 x!=0  000-999         共abc*1000
  1.2 x==0  001-abc-1       共001-abc-1 * 1000
2.abc x
  2.1 d<x                   共0
  2.2 d==x  000-efg         共efg+1
  2.3 d>x   000-999         共1000
 */
#include <iostream>
#include <vector>
using namespace std;

int a, b;

// 10^t
int pow10(int t)
{
    int res = 1;
    while (t--)
        res *= 10;
    return res;
}

// 返回num中l-r的数
int getnum(vector<int> num, int l, int r)
{
    int res = 0;
    for (int i = l; i >= r; i--)
        res = res * 10 + num[i];
    return res;
}

// x在1-n中出现的次数
int count(int n, int x)
{
    if (!n)
        return 0;
    int res = 0;
    vector<int> num;
    while (n)
    {
        num.push_back(n % 10);
        n /= 10;
    }

    n = num.size();
    // 如果x == 0，就得从第二位开始枚举，因为首位不能为0
    for (int i = n - 1 - !x; i >= 0; i--)
    {
        if (i < n - 1) // 枚举第一位的话没有这种情况
        {
            res += getnum(num, n - 1, i + 1) * pow10(i);
            if (!x)
                res -= pow10(i);
        }

        if (num[i] == x)
            res += getnum(num, i - 1, 0) + 1;
        if (num[i] > x)
            res += pow10(i);
    }

    return res;
}

int main()
{
    while (cin >> a >> b && (a || b))
    {
        if (a > b)
            swap(a, b);

        for (int i = 0; i <= 9; i++)
            cout << count(b, i) - count(a - 1, i) << " ";
        cout << endl;
    }

    return 0;
}