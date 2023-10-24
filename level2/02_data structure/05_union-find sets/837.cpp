// acwing 837 连通块中点的数量
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int p[N], s[N]; // s[i] 表示根节点为i的集合中点的数量

int find(int x)
{
    if (x != p[x])
        p[x] = find(p[x]);
    return p[x];
}

void merge(int a, int b)
{
    int x = find(a), y = find(b);
    p[x] = y;
    s[y] += s[x];
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        p[i] = i;
        s[i] = 1;
    }

    while (m--)
    {
        char op[3];
        int a, b;
        scanf("%s", op);
        if (op[0] == 'C')
        {
            scanf("%d%d", &a, &b);
            if (find(a) == find(b))
                continue;
            merge(a, b);
        }
        else if (op[1] == '1')
        {
            scanf("%d%d", &a, &b);
            if (find(a) == find(b))
                printf("%s\n", "Yes");
            else
                printf("%s\n", "No");
        }
        else
        {
            scanf("%d", &a);
            printf("%d\n", s[find(a)]);
        }
    }

    return 0;
}