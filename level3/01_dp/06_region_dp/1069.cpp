// acwing 1069 凸多边形的划分
/*
    将一个n边型划分为n-2个三角形，可以先固定一条边，枚举将这一条边构成的三角形的方案
    例如先确定1-n这条边，然后枚举(1, k, n)这三个点构成的三角形，这样多边形就被分为了左侧以(1,k)为底边，右侧以(k,n)为底边，
    中间是(1,k,n)三角形这样的三部分，最终结果就是左侧最小值+右侧最小值+w[1]*w[k]*w[n]

    状态表示：f[l][r]表示n边型(l, l+1, l+2, ... r-1, r, l)以(l, r)划分为n-2个三角形得到权值的最小值
    状态计算：以(l,r)为底边，枚举第三个点，将n边型划分为三部分，然后求解左侧最小值+中间三角形+右侧最小值
*/
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f
typedef long long LL;
const int N = 55, M = 35;
int w[N];
vector<int> f[N][N];
int n;

vector<int> add(vector<int> &a, vector<int> &b)
{
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size() || i < b.size(); i++)
    {
        if (i < a.size())
            t += a[i];
        if (i < b.size())
            t += b[i];
        c.push_back(t % 10);
        t /= 10;
    }
    if (t)
        c.push_back(t);
    return c;
}

bool cmp(vector<int> &a, vector<int> &b)
{
    if (a.size() != b.size())
        return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i--)
        if (a[i] != b[i])
            return a[i] < b[i];
    return true;
}

vector<int> mul(vector<int> &a, LL b)
{
    vector<int> c;
    LL t = 0;
    for (int i = 0; i < a.size(); i++)
    {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while (t)
    {
        c.push_back(t % 10);
        t /= 10;
    }
    return c;
}

void slove(vector<int> &temp, int num)
{
    while (num)
    {
        temp.push_back(num % 10);
        num /= 10;
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    vector<int> temp;
    for (int len = 3; len <= n; len++)
        for (int l = 1; l + len - 1 <= n; l++)
        {
            int r = l + len - 1;
            f[l][r] = vector<int>(M, 1);    // f[l][r]的每一位都是1
            for (int k = l + 1; k < r; k++)
            {
                temp.clear();
                slove(temp, w[l]);
                temp = mul(temp, w[k]);
                temp = mul(temp, w[r]);
                temp = add(temp, f[l][k]);
                temp = add(temp, f[k][r]);
                if (cmp(temp, f[l][r]))
                    f[l][r] = temp;
            }
        }
    for (int i = f[1][n].size() - 1; i >= 0; i--)
        cout << f[1][n][i];
    cout << endl;
    return 0;
}