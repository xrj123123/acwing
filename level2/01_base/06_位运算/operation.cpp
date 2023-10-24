// 位运算常用操作
#include <iostream>
using namespace std;
int main()
{
    // 1.输出n的二进制的第k位  n >> k & 1
    int n = 10;
    for (int k = 3; k >= 0; k--)
        cout << ((n >> k) & 1) << endl;

    // 2.lowbit(x)  返回x的最后一位1。  例如x=1010  返回10;    x=101000  返回1000
    // 实现方式 : x & -x = x & (~x + 1 )

    return 0;
}