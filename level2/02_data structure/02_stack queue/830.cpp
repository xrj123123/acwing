// acwing 830 单调栈    一般题型为：在一个数轴上，找到在某一个数左(右)边，离他最近且比他小(大)的数
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int stk[N], tt;
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        while (tt && stk[tt] >= x) // 栈非空，并且栈顶元素大于x，那么栈顶元素出栈
            tt--;

        if (tt) // 栈非空，输出栈顶元素
            printf("%d ", stk[tt]);
        else // 空栈
            printf("%s ", "-1");
        stk[++tt] = x;
    }
    printf("\n");
    return 0;
}