// acwing 827 双链表
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int l[N], r[N], e[N], idx;
// l[i]表示i左边的点
// r[i]表示i右边的点

void init()
{
    // 0是头结点，1是尾结点,只充当头尾结点，不存数据
    r[0] = 1;
    l[1] = 0;
    idx = 2;
}

// 在k的右边插入x
void add(int k, int x)
{
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    l[r[k]] = idx;
    r[k] = idx;
    idx++;
}

// 删除第k个节点
void remove(int k)
{
    r[l[k]] = r[k];
    l[r[k]] = l[k];
}

int main()
{
    int m;
    cin >> m;
    init();
    while (m--)
    {
        int k, x;
        string op;
        cin >> op;
        if (op == "L") // 在链表最左端插入x
        {
            cin >> x;
            // 最左端插入也就是在0号节点右边插入
            add(0, x);
        }
        else if (op == "R") // 在链表最右边插入
        {
            cin >> x;
            add(l[1], x);
        }
        else if (op == "D") // 删除第k个插入的节点
        {
            cin >> k;
            remove(k + 1);
        }
        else if (op == "IL") // 在第 k 个插入的数左侧插入一个数
        {
            cin >> k >> x;
            add(l[k + 1], x);
        }
        else if (op == "IR") // 在第 k 个插入的数右侧插入一个数
        {
            cin >> k >> x;
            add(k + 1, x);
        }
    }
    for (int i = r[0]; i != 1; i = r[i])
        cout << e[i] << " ";
    cout << endl;

    return 0;
}