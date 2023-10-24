// acwing 187 导弹防御系统
/*
    贪心 + dp + dfs
    贪心流程:
        从前到后依次枚举每个数：
            上升子序列：case1:当前数小于前边所有序列结尾的数，则创建新的序列
                       case2:找到现有的序列中结尾数小于等于当前数最大的数，将其加入该序列
            下降子序列: case3:当前数大于现有所有序列的结尾数，则创建新的序列
                       case4:找到现有序列中结尾数大于等于当前数最小的数，将其加入该序列                         
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 55;
int q[N], up[N], down[N];
int n, res;

// u表示搜索到第个数,su表示上升的序列数量，sd表示下降序列的数量
void dfs(int u, int su, int sd)
{
    if (su + sd >= res)
        return;
    if (u == n)
    {
        res = su + sd;
        return;
    }

    // 上升子序列,在up中找到小于等于q[u]的最大的数，将其变为q[u]
    int k = 0;
    while (k < su && up[k] > q[u])  k++;
    int t = up[k];
    up[k] = q[u];
    if (k < su)
        dfs(u + 1, su, sd);
    else
        dfs(u + 1, su + 1, sd);
    up[k] = t;

    // 下降子序列,在down中找到大于等于q[u]的最小数，将其变为q[u]
    k = 0;
    while (k < sd && down[k] < q[u]) k++;
    t = down[k];
    down[k] = q[u];
    if (k < sd)
        dfs(u + 1, su, sd);
    else
        dfs(u + 1, su, sd + 1);
    down[k] = t;
}

int main()
{
    while (cin >> n, n)
    {
        for (int i = 0; i < n; i++)
            cin >> q[i];
        
        res = n;

        dfs(0, 0, 0);

        cout << res << endl;
    }

    return 0;
}


