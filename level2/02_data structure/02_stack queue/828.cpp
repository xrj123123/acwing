// acwing 828 模拟栈
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int stk[N], tt; // tt为栈顶
int main()
{
    int m;
    cin >> m;
    while (m--)
    {
        string op;
        int x;
        cin >> op;
        if (op == "push")
        {
            cin >> x;
            stk[++tt] = x;
        }
        else if (op == "pop")
        {
            tt--;
        }
        else if (op == "empty")
        {
            if (tt > 0)
                cout << "NO" << endl;
            else
                cout << "YES" << endl;
        }
        else
        {
            cout << stk[tt] << endl;
        }
    }

    return 0;
}