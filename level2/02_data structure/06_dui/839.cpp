// acwing 839 模拟堆
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5 + 10;
int h[N], size, ph[N], hp[N]; // ph[k]表示第k个插入的点在堆里的下标是什么，hp[j]表示堆里第j个点是第几个插入的

// 将堆里边第a个和第b个元素交换
void heap_swap(int a, int b)
{
    swap(ph[hp[a]], ph[hp[b]]);
    swap(hp[a], hp[b]);
    swap(h[a], h[b]);
}

void down(int u)
{
    int t = u;
    if (2 * u <= size && h[t] > h[2 * u])
        t = 2 * u;
    if (2 * u + 1 <= size && h[t] > h[2 * u + 1])
        t = 2 * u + 1;
    if (t != u)
    {
        heap_swap(t, u);
        down(t);
    }
}

void up(int u)
{
    while (u / 2 && h[u] < h[u / 2])
    {
        heap_swap(u, u / 2);
        u /= 2;
    }
}

int main()
{
    int n;
    int m = 0; // 第m个插入的
    scanf("%d", &n);
    while (n--)
    {
        char op[5];
        int x, k;   
        scanf("%s", op);
        if (!strcmp(op, "I"))
        {
            scanf("%d", &x);
            hp[++size] = ++m;
            ph[m] = size;
            h[size] = x;
            up(size);
        }
        else if (!strcmp(op, "PM"))
            printf("%d\n", h[1]);
        else if (!strcmp(op, "DM"))
        {
            heap_swap(1, size);
            size--;
            down(1);
        }
        else if (!strcmp(op, "D"))
        {
            scanf("%d", &k);
            k = ph[k];
            heap_swap(size, k);
            size--;
            down(k);
            up(k);
        }
        else
        {
            scanf("%d%d", &k, &x);
            h[ph[k]] = x;
            down(ph[k]);
            up(ph[k]);
        }
    }

    return 0;
}