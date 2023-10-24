// acwing 869 试除法求约数
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n;

// 返回n的约数
auto get_divisors(int n)
{
    vector<int> res;
    for (int i = 1; i <= n / i; i++)
    {
        if (n % i == 0)
        {
            res.push_back(i);
            if (i != n / i)
                res.push_back(n / i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}

int main()
{
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        auto res = get_divisors(x);
        for (auto x : res)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}