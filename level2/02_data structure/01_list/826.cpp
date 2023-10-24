// acwing 826 单链表
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int head, e[N], ne[N], idx;
// head表示头结点
// e[i]表示第i个点的值
// ne[i]表示第i个点的下一个点
// idx表示使用到了第几个点

void init()
{
    head = -1;
    idx = 0;
}

// 头插法
void add_to_head(int x)
{
    e[idx] = x;
    ne[idx] = head;
    head = idx;
    idx++;
}

// 将x插入到下标是k的点后边
void add(int k, int x)
{
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx++;
}

// 将下标是k的点的后一个点删除
void remove(int k)
{
    ne[k] = ne[ne[k]];
}

int main()
{
    int m;
    cin >> m;
    init();
    while (m--)
    {
        int k, x;
        char op;
        cin >> op;
        if (op == 'H')
        {
            cin >> x;
            add_to_head(x);
        }
        else if (op == 'D')
        {
            cin >> k;
            if (!k)
                head = ne[head];
            else
                remove(k - 1);
        }
        else
        {
            cin >> k >> x;
            add(k - 1, x);
        }
    }
    for (int i = head; i != -1; i = ne[i])
        cout << e[i] << " ";
    cout << endl;

    return 0;
}