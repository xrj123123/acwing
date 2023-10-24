// acwing 913 排队打水
/*
    按时间从小到大排序
*/
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int t[N];
int n;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> t[i];

    sort(t, t + n);

    long long res = 0;
    for (int i = 0; i < n - 1; i++)
        res += (n - i - 1) * t[i];

    cout << res << endl;

    return 0;
}
