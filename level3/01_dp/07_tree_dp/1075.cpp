// acwing 1075 数字转换
/*
    每个数字的约数之和是固定的，且只有一个，因此可以将某个数字的约数之和作为他的父节点
    所有数字就会组成一个森林，最终要求的就是树的最长路径

    例如x的约数为y，x可以转化为y，y可以转化为x，但是这里让y作为x的父节点，建立有向树。
    因为每次dfs都是从根节点开始的，有根节点的树的最长路径一定会经过从根节点递归到的某个节点
    但是在1072树的最长路径这道题中，没有固定哪个点是根节点
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 50010;
int h[N], e[N], ne[N], idx;
int sum[N]; // sum[i]表示数字i的约数大小
int st[N];  // st[i]=false表示节点i为根节点
int n, res;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int dfs(int u)
{
    int d1 = 0, d2 = 0;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        int d = dfs(j) + 1;
        if (d > d1)
            d2 = d1, d1 = d;
        else if(d > d2)
            d2 = d;
    }
    res = max(res, d1 + d2);
    return d1;
}

int main()
{
    cin >> n;
    memset(h, -1, sizeof h);
    // 如果用试除法求约数，时间复杂度为O(n*sqrt(n)),这种求法时间复杂度为nlogn
    for (int i = 1; i <= n; i++)
        for (int j = 2; j <= n / i; j++)
            sum[i * j] += i;
            
    for (int i = 2; i <= n; i++)
        if (sum[i] < i)
        {
            add(sum[i], i);
            st[i] = true;
        }
            
    for (int i = 1; i <= n; i++)
        if (!st[i])
            dfs(i);

    cout << res << endl;
    
    return 0;
}