// acwing 104 货仓选址
/*
    f(x) = |x1-x| + |x2-x| + ... +|xn-x|
    f(x) = (|x1-x| + |xn-x|) + (|x2-x| + |xn-1 -x|) + ...
        >= xn - x1 + xn-1 - x2 +...
    当x选址在每两个的中间就可以取最小值，即等号成立
*/
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int a[N];
int n;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a, a + n);

    int tmp = a[n / 2];

    int res = 0;
    for(int i = 0; i < n; i++)
        res += abs(tmp - a[i]);

    cout << res << endl;

    return 0;
}