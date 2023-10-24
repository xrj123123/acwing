// acwing 902 最短编辑距离
/*
    状态表示: f[i][j] 表示a的前i个字母变成b的前j个字母所需的最少操作数
    状态计算: 增加, a的前i个字母和b的前j-1个字母相同，那么增加一个字母 f[i][j-1] + 1
             删除, a的前i-1个字母和b的前j个字母相同，那么删除a的最有一个字母,f[i-1][j] + 1
             修改, a的前i-1个字母和b的前j-1个字母相同，但a[i]!=b[j],则f[i-1][j-1]+1, 若a[i]==b[j],则f[i-1][j-1]
*/
#include <iostream>
using namespace std;
const int N = 1010;
char a[N], b[N];
int f[N][N];
int n, m;

int main()
{
    scanf("%d%s", &n, a + 1);
    scanf("%d%s", &m, b + 1);

    for (int i = 1; i <= m; i++) // a的前0个和b的前i个要相同，则给a增加i个
        f[0][i] = i;

    for (int i = 1; i <= n; i++) // a的前i个要和b的前0个相同，则删除i个
        f[i][0] = i;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            f[i][j] = min(f[i - 1][j] + 1, f[i][j - 1] + 1);
            if (a[i] != b[j])
                f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
            else
                f[i][j] = min(f[i][j], f[i - 1][j - 1]);
        }

    cout << f[n][m] << endl;

    return 0;
}