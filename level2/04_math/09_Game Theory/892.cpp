// acwing 892 台阶-Nim游戏
/*
    必胜状态：奇数台阶异或不为0，总能找到一种方式使奇数台阶异或为0，
            偶数台阶移动到0层需要偶数次，因此对方移动，我也移动
    必败状态：奇数台阶异或为0，不会怎么调整，下一个状态奇数台阶异或总是不为0

*/
#include <iostream>
using namespace std;
int main()
{
    int n, x;
    int res = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        if (i % 2)
            res = res ^ x;
        }
    if (res)
        puts("Yes");
    else
        puts("No");
    return 0;
}