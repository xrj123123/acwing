// acwing 836 合并集合
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int p[N];

int find(int x) // 返回x的父节点
{
    if (x != p[x])
        p[x] = find(p[x]);
    return p[x];
}

void merge(int a, int b) // 将a和b合并
{
    int x = find(a), y = find(b);
    p[x] = y;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        p[i] = i;

    while (m--)
    {
        char op[2]; // scanf读入字符的时候会读入不必要的空格回车，而读入字符串就会忽略空格和回车，因此采用字符串方法
        int a, b;
        scanf("%s%d%d", &op, &a, &b);
        if (op[0] == 'M')
            merge(a, b);
        else
        {
            if (find(a) == find(b))
                puts("Yes");
            else
                puts("No");
        }
    }

    return 0;
}