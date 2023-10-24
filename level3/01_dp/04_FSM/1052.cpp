// acwing 1052 设计密码
/*
    状态机 + KMP
    如果当前设计的密码是合法的话，在他后面添加一个新字符，可能导致新密码不合法，只有可能是新密码的后缀子串
    出现了T，因此通过线性构造方法，只需判断后缀子串是否出现T即可。kmp中用j表示母串后缀与模式串匹配的最大长度

    状态表示：f[i][j]表示密码生成了i位，并且第i位匹配到字符串T中位置j(密码的后缀与模式串匹配的最大长度为j)的方案数
    状态计算：枚举第i+1位的字母a、b、c...z
            当s[i+1] == 'a' 
                第i+1位匹配到T中的位置为u
                当第i+1位是'a'时，f[i][j]能转移到的位置为f[i+1][u]
                f[i+1][u] = f[i+1][u] + f[i][j]
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 55, MOD = 1e9 + 7;
int f[N][N];
char str[N];    //  模式串
int ne[N];
int n, m;

int main()
{
    cin >> n;
    cin >> str + 1;
    m = strlen(str + 1);

    // 构造ne数组
    for (int i = 2, j = 0; i <= m; i++)
    {
        while (j && str[i] != str[j + 1])
            j = ne[j];
        if (str[i] == str[j + 1])
            j++;
        ne[i] = j;
    }

    f[0][0] = 1;    // 生成了0位，匹配的子串位置是0的方案数为1
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) // j是第i为密码匹配到的位置，因为不能包含子串，因此不能匹配到m
            for (char k = 'a'; k <= 'z'; k++)   // 枚举第i+1位可能出现的字母
            {
                // 匹配过程：寻找第i+1位的字母为k时，且密码已经生成了i位，匹配的子串位置为j时，可以跳到哪里
                int u = j;
                while (u && str[u + 1] != k)
                    u = ne[u];
                if (str[u + 1] == k)
                    u++;
                if (u < m)
                    f[i + 1][u] = (f[i + 1][u] + f[i][j]) % MOD;
            }

    int res = 0;
    for (int i = 0; i < m; i++)
        res = (res + f[n][i]) % MOD;

    cout << res << endl;

    return 0;
}