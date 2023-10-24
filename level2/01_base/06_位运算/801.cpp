// acwing 801 二进制中1的个数
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int n;
int a[N];

// 返回x的二进制的最后一位1
int lowbit(int x)
{
    return x & -x;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
    {
        int res = 0;
        while (a[i])
        {
            a[i] -= lowbit(a[i]);
            res++;
        }
        cout << res << " ";
    }
    cout << endl;

    return 0;
}