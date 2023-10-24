// acwing 831 KMP字符串
/*
    只通过模板串就可以求出next数组
    next[i]表示以i为终点的后缀和从1开始的前缀相等，并且后缀长度最长
    next[i] = j表示p[1, j] == p[i - j + 1, i]
*/
#include <iostream>
using namespace std;
const int N = 100010, M = 1000010;
int n, m;
char p[N], s[M];
int ne[N];
int main()
{
    cin >> n >> p + 1 >> m >> s + 1; // 模式串p在s中出现

    // 求next的过程
    // ne[1]=0, 第一个字母失败了，那么就只能从0开始
    // abababcba
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j && p[i] != p[j + 1])
            j = ne[j];
        if (p[i] == p[j + 1])
            j++;
        ne[i] = j;
    }

    // kmp匹配过程
    // 主串s下标从1开始，模板串p下标从0开始
    for (int i = 1, j = 0; i <= m; i++)
    {
        // 当前模板串没有退到0，并且s[i]和p[j+1]不匹配，那么j就往回跳, j = ne[j]，然后继续让s[i]和p[j+1]匹配
        while (j && s[i] != p[j + 1])
            j = ne[j];
        // 如果s[i]和p[j+1]匹配了，那么j++，去匹配下一个位置
        if (s[i] == p[j + 1])   
            j++;
        // 如果j == n，因为s[i]和p[j+1]进行匹配，所以j = n, 那么该匹配p[n+1]，匹配结束
        if (j == n)
        {
            printf("%d ", i - n);   // 题目下标从0开始，这里是从1开始，因此 i - n + 1还要减个1
            j = ne[j];  // 匹配成功后，j=ne[j]，去匹配下一个
        }
    }
    puts("");

    return 0;
}