// acwing 890 能被整除的数
/*
    两个集合的并集：S1+S2-S1∩S2     C(2,1)-C(2,2)
    三个集合的并集：S1+S2+S3-S1∩S2-S1∩S3-S2∩S3+S1∩S2∩S3     C(3,1)-C(3,2)+C(3,3)
    容斥原理
    时间复杂度2^n
    C(n,0)+C(n,1)+C(n,2)+...+C(n,n) = 2^n
    C(n,1)+C(n,2)+...+C(n,n) = 2^n-C(n,0) = 2^n-1

    1-10中2和3的倍数的个数
    S2:2,4,6,8,10
    S3:3,6,9
    |S2∪S3| = |S2| + |S3| - |S2∩S3| = 5 + 3 -1 = 7
    |S2| = n/2  |S3| = n/3  |S2∩S3| = n/6
    001 + 010 + 100 - 011 - 101 - 110 + 111
    这里用位运算表示，当有m个质数时，从1枚举到2^m-1，总共2^m-1种状态，枚举每种状态中1的个数，1的个数为奇数就加，偶数就减
*/
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 20;
int n, m;
int p[N];
int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        cin >> p[i];

    int res = 0;
    for (int i = 1; i < 1 << m; i++)
    {
        int t = 1, cnt = 0;         // t表示当前集合中元素乘积的大小，cnt表示当前数中1的个数
        for (int j = 0; j < m; j++) // 枚举m位
        {
            if (i >> j & 1)
            {
                // 乘积>0，则n/t = 0，跳过
                if ((LL)t * p[j] > n)
                {
                    t = -1;
                    break;
                }
                cnt++;
                t = t * p[j];
            }
        }
        if (t != -1)
        {
            if (cnt % 2)
                res += n / t;
            else
                res -= n / t;
        }
    }
    cout << res << endl;

    return 0;
}