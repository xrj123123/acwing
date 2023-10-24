// acwing 891 Nim游戏
/*
    先手必胜状态：可以走到某一个必败状态
    先手必败状态：走不到任何一个必败状态

    n堆石子个数:a1、a2、a3...an
    如果a1^a2^a3^...^an = 0, 先手必败
                        ≠0, 先手必胜

    1、0^0^0...^0 = 0  (必败)
    2、a1^a2^a3...^an = x ≠0 (此时一定可以通过某种方式，让异或值为0)
        假设x的二进制中最高一位1在第k位
        则a1、a2、...an中必有一个ai的第k位为1
        有ai^x < ai     此时从ai中拿走ai-(ai^x)个石子，剩余ai^x个石子
        将ai变为ai^x,则a1^a2^a3...ai^x...^an = x^x = 0
    3、a1^a2^a3...^an = 0   此时无论拿走几个，剩下的异或起来一定不为0
        反证法：假设将ai拿走后剩余ai'，异或起来=0
        a1^a2^a3...^an = 0
        a1^a2^a3...^ai'^ai+1...^an = 0
        将两个式子左右异或，则ai^ai'=0,则ai=ai',矛盾

    综上，先手的时候，如果异或值不为0，那么拿走一定数量后，一定可以让异或值为0
                    如果异或值为0，那么不管拿多少后，异或值都不为0
*/
#include <iostream>
using namespace std;
int main()
{
    int n;
    int res = 0;
    cin >> n;
    while (n--)
    {
        int a;
        cin >> a;
        res = res ^ a;
    }
    if (res)
        puts("Yes");
    else
        puts("No");

    return 0;
}