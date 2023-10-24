// acwing 835 Trie字符串统计
// Trie树：高效地存储和查找字符串集合的数据结构
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
// son[i][j]表示第i个位置(idx)的字母下一个字母为j在几号节点(idx)
// cnt[i] 表示以i位置(idx)结尾的字符串的个数
// 下标为0的点，既是根节点，也是空节点
int son[N][26], cnt[N], idx;
char str[N];

void insert(char str[])
{
    int p = 0;
    for (int i = 0; str[i]; i++)
    {
        int u = str[i] - 'a';
        if (!son[p][u]) // 该节点不存在，就创建他
            son[p][u] = ++idx;
        p = son[p][u]; // 到下一个节点的位置
    }
    cnt[p]++; // 记录以此节点结束的字符串的个数
}

int query(char str[])
{
    int p = 0;
    for (int i = 0; str[i]; i++)
    {
        int u = str[i] - 'a';
        if (!son[p][u])
            return 0;
        p = son[p][u];
    }
    return cnt[p];
}

int main()
{
    int n;
    char op[2];
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s%s", &op, &str);
        if (op[0] == 'I')
            insert(str);
        else
            printf("%d\n", query(str));
    }

    return 0;
}