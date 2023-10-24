// acwing 799 最长连续不重复子序列  双指针解法
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int n;
int a[N], s[N]; // s[N]表示区间中各个数字的个数
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int res = 0;
    for (int i = 0, j = 0; i < n; i++)
    {
        s[a[i]]++;
        while (s[a[i]] > 1)
        {
            s[a[j]]--;
            j++;
        }
        res = max(res, i - j + 1);
    }
    cout << res << endl;

    return 0;
}