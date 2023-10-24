// acwing 125 耍杂技的牛
/*
    按照wi+si从小到大的顺序排，则最大的危险系数最小

    证明：
        贪心得到的答案 >= 最优解
        贪心得到的答案 <= 最优解

    假设最优解不是按wi + si从小到大的顺序排列得到的

    wi + si > w(i+1) + s(i+1)

                第i只牛                      第i+1只牛
    交换前    w1+w2+...+w(i-1)-si       w1+w2+...+wi-s(i+1)
    交换后    w1+w2+...+w(i-1)-s(i+1)   w1+w2+...+w(i-1)+w(i+1)-si

    交换前      -si                     wi-s(i+1)
    交换后      -s(i+1)                 w(i+1)-si

    交换前      s(i+1)                  wi+si
    交换后      si                      w(i+1)+s(i+1)

    因为wi+si > si 且 wi+si > w(i+1)+s(i+1)
    所以交换前的最大值一定大于交换后的最大值，所以贪心得到的答案 <= 最优解
    所以贪心得到的答案 == 最优解
*/
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> PII;
const int N = 5e4 + 10;
PII cow[N];
int n;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int w, s;
        cin >> w >> s;
        cow[i] = {w + s, w};
    }
    sort(cow, cow + n);

    int res = -2e9, sum = 0; // sum记录累计重量
    for (int i = 0; i < n; i++)
    {
        res = max(res, sum - (cow[i].first - cow[i].second));
        sum += cow[i].second;
    }

    cout << res << endl;

    return 0;
}