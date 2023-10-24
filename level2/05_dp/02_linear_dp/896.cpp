// acwing 896 最长上升子序列II
/*
    样例: 3 1 2 1 8 5 6 ,   最长递增子序列为 1 2 5 6
    传统方法两层循环，这道题n = 100000，显然超时
    
    i=1,最长为1，数字为3
    i=2,最长为1，数字为3或1，此时可以发现，比3大的一定比1大，因此最长上升子序列一定是从1这里出发
                 因此可以用1代替3
    i=3,最长为2，数字为1，2
    i=4,最长为2，数字为1，2
    i=5,最长为3，数字为1，2，8      ，若当前比较的数字，比维护的数组的最后一位还大，那么直接加入
    i=6,最长为3，数字为1，2，5      ，若当前比较的数字，小于等于数组的最后一位，
                                      那么找到大于等于这个数字的最小值的下标，将其变为该数字
    i=7,最长为4，数字为1，2，5，6
    
    最后维护的数组一定是单调递增的序列
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int a[N];
int q[N];
int n;

// 找到>=x的最小值
int find(int l, int r, int x)
{
    while(l < r)
    {
        int mid = l + r >> 1;
        if (q[mid] >= x)
            r = mid;
        else 
            l = mid + 1;
    }
    return l;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
        
    int cnt = 0;
    q[0] = -2e9;
    for(int i = 1; i <= n; i++)
    {
        if(a[i] > q[cnt])
            q[++cnt] = a[i];
        else
        {
            int idx = find(0, cnt, a[i]);
            q[idx] = a[i];
        }
    }
    
    cout << cnt << endl;
    
    return 0;
}
