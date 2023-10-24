// acwing 888 求组合数 IV
/*
    不取模，需要用高精度将这个数算出来
    1.分解质因数    C(a,b) = a! / ((a-b)! * b!),将a、a-b、b分别质因数分解，然后将质因数相乘
    2.高精度乘法
*/
#include <iostream>
#include <vector>
using namespace std;
const int N = 5010;
int primes[N], cnt;
int sum[N]; // 获取质数的个数
bool st[N];

// 线性筛
void get_primes(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!st[i])
            primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++)
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

// 获取n!中p的个数
/*
    n里面p的个数 = n/p + n/p^2 + n/p^3...
    例如8！中2的个数，8/2+8/4+8/8=7个
*/
int get(int n, int p)
{
    int res = 0;
    while (n)
    {
        res += n / p;
        n /= p;
    }
    return res;
}

vector<int> mul(vector<int> a, int b)
{
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); i++)
    {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while (t)   //  需要进行很多次高精度乘法，如果这里用if的话，当c的某个位置存的数字稍微大一点，和b相乘就越界了
    {
        c.push_back(t % 10);
        t /= 10;
    }
    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
    return c;
}

int main()
{
    int a, b;
    cin >> a >> b;
    get_primes(a); // 得到a以内的质数

    // 质因数分解，获取各个质数的个数
    for (int i = 0; i < cnt; i++)
    {
        int p = primes[i];
        sum[i] = get(a, p) - get(b, p) - get(a - b, p);
    }

    // 高精度乘法
    vector<int> res;
    res.push_back(1);
    for (int i = 0; i < cnt; i++)
        for (int j = 0; j < sum[i]; j++)
            res = mul(res, primes[i]);

    for (int i = res.size() - 1; i >= 0; i--)
        cout << res[i];
    cout << endl;

    return 0;
}
