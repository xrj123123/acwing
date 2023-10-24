// acwing 479 加分二叉树
/*
    中序遍历实际上可以将二叉树向下投影，投影出的序列就是中序遍历
    求得分最大值，枚举每个根节点，然后计算根节点左边的得分和右边的得分，最后计算出总得分

    状态表示：f[l, r]表示区间[l, r]的中序遍历，可以获得的得分的最大值
    状态计算：f[l, r] = max(f[l, r], f[l, k - 1] * f[k + 1, r] + w[k]);
*/
#include <iostream>
using namespace std;

const int N = 35;
int n;
int w[N];
int f[N][N], g[N][N];   // g[l][r]表示区间[l, r]这一段中序遍历序列的根节点

void dfs(int l, int r)
{
    if (l > r) return;
    int root = g[l][r];
    cout << root << " ";
    dfs(l, root - 1);
    dfs(root + 1, r);    
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    
    for (int len = 1; len <= n; len++)
        for (int l = 1; l + len - 1 <= n; l++)
        {
            int r = l + len - 1;
            if (len == 1)   // 区间长度为1，就是叶节点
            {
                f[l][r] = w[l];
                g[l][r] = l;
                continue;
            }
            for (int k = l; k <= r; k++)
            {
                int left = k == l ? 1 : f[l][k - 1];
                int right = k == r ? 1 : f[k + 1][r];
                int score = left * right + w[k];
                if (score > f[l][r])
                {
                    f[l][r] = score; 
                    g[l][r] = k;
                }           
            }
        }
    cout << f[1][n] << endl;
    dfs(1, n);
    return 0;
}