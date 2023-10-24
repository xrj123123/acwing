// acwing 885 求组合数 I
/*
    此题n的范围为10000，a和b的范围为2000，时间复杂度为2*10^8，暴力会超时
    因此可以预先处理出来每对C(a,b)的值，2000*2000=4*10^6   O(n^2)   n为a、b范围
    由组合数加法:C(a,b) = C(a-1,b) + C(a-1,b-1)
*/
#include <iostream>
using namespace std;
const int N = 2010, mod = 1e9 + 7;
int c[N][N];

void init()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
            if (!j)
                c[i][j] = 1;
            else
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
}

int main()
{

    int n;
    cin >> n;
    init();
    
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        cout << c[a][b] << endl;
    }

    return 0;
}