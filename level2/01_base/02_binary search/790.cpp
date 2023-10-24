// acwing 790 数的三次方根
#include <iostream>
#include <iomanip>
using namespace std;

double x;
int main()
{
    cin >> x;
    if (x < 0)
    {
        cout << "-";
        x = -x;
    }

    double l = 0, r = x;
    if (x < 1)
        l = 0, r = 1;

    while (l + 1e-8 < r)
    {
        double mid = (l + r) / 2;
        if (mid * mid * mid >= x)
            r = mid;
        else
            l = mid;
    }

    cout << fixed << setprecision(6) << l << endl;

    return 0;
}