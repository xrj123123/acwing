// acwing 272 最长公共上升子序列
/*
    状态表示:
        集合: f[i][j]表示A序列的前i个字母和B序列的前j个字母，且以B[j]结尾的最长公共子序列
        属性: max
    状态计算:
        将f[i][j]划分为包含a[i]和不包含a[i]的集合
        不包含a[i]：f[i - 1][j]
        包含a[i]: 又因为是以b[j]结尾，所以a[i] == b[j], 找到从0到k-1之间比b[j]小的数,f[i - 1][k] + 1
*/
#include <iostream>
using namespace std;

const int N = 3010;
int a[N], b[N];
int f[N][N];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]);

/*
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            f[i][j] = f[i - 1][j];
            if (a[i] == b[j])
            {
                f[i][j] = max(f[i][j], 1);
                for (int k = 1; k < j; k++)
                    if (b[k] < b[j]) 
                        f[i][j] = max(f[i][j], f[i - 1][k] + 1);
            }
        }
 */
/*
    优化:第三层循环在a[i] == b[j]时，如果b[k] < b[j]时执行，可以换为b[k] < a[i], 即找到在b[k] < a[i]时,f[i - 1][k]+1的最大值
*/ 
    for (int i = 1; i <= n; i++)
    {
        int maxv = 1;   // 
        for (int j = 1; j <= n; j++)
        {
            f[i][j] = f[i - 1][j];
            if (a[i] == b[j])   f[i][j] = max(f[i][j], maxv);
            if (a[i] > b[j])    maxv = max(maxv, f[i - 1][j] + 1);
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++)
        res = max(res, f[n][i]);
    
    cout << res << endl;

    return 0;
}