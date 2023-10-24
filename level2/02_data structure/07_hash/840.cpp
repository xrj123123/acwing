// acwing 840 模拟散列表
// 离散化是一种特殊的hash，离散化需要保证有序性
// 1.开放寻址法     2.拉链法
// 拉链法
/* #include <iostream>
#include <cstring>
using namespace std;
const int N = 100003; // 模数最好取质数，且离2的整次幂远，这样冲突概率低
int h[N], idx, e[N], ne[N];

void insert(int x)
{
    int k = (x % N + N) % N; // 防止x为负数，所以+N
    e[++idx] = x;
    ne[idx] = h[k];
    h[k] = idx;
}

bool query(int x)
{
    int k = (x % N + N) % N;
    for (int i = h[k]; i != -1; i = ne[i])
        if (e[i] == x)
            return true;
    return false;
}

int main()
{
    int n;
    scanf("%d", &n);
    memset(h, -1, sizeof(h)); // 初试头结点都为-1
    while (n--)
    {
        char op[2];
        int x;
        scanf("%s%d", op, &x);
        if (op[0] == 'I')
            insert(x);
        else if (op[0] == 'Q')
        {
            if (query(x))
                printf("%s\n", "Yes");
            else
                printf("%s\n", "No");
        }
    }

    return 0;
} */

// 开放寻址法
#include <iostream>
#include <cstring>
using namespace std;
#define null 0x3f3f3f3f
const int N = 200003; // 开放寻址法，数组应该开到题目要求范围的2-3倍
int h[N];

// 如果x在hash表中，返回x所在位置，如果不在，返回应该插入的位置
int find(int x)
{
    int k = (x % N + N) % N;

    while (h[k] != null && h[k] != x)
    {
        k++;
        if (k == N)
            k = 0;
    }
    return k;
}

int main()
{
    int n;
    scanf("%d", &n);
    memset(h, 0x3f, sizeof(h)); // memset按字节来设置，h是int型，每个有4个字节，设置完就是0x3f3f3f3f
    while (n--)
    {
        char op[2];
        int x;
        scanf("%s%d", op, &x);
        if (op[0] == 'I')
        {
            int k = find(x);
            h[k] = x;
        }
        else
        {
            if (h[find(x)] == null)
                printf("%s\n", "No");
            else
                printf("%s\n", "Yes");
        }
    }

    return 0;
}