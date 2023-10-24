// 浮点数二分模板
// 求sqrt(x)
// 一般设置精度为要求精度的后两位，比如要求小数点后四位，就设为6位
#include <iostream>
using namespace std;

double x;

int main()
{
    cin >> x;
    double l = 0, r = x;
    while (l + 1e-8 < r)
    {
        double mid = (l + r) / 2;
        if (mid * mid <= x)
            l = mid;
        else
            r = mid;
    }
    cout << l << endl;

    return 0;
}

// 第二种写法，循环100次
/* #include <iostream>
using namespace std;

double x;

int main()
{
    cin >> x;
    double l = 0, r = x;
    for(int i=0;i<100;i++)
    {
        double mid = (l + r) / 2;
        if (mid * mid <= x)
            l = mid;
        else
            r = mid;
    }
    cout << l << endl;

    return 0;
} */
