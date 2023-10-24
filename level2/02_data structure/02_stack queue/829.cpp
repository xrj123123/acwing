// acwing 829 模拟队列
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int q[N], hh, tt = -1; // hh为队尾，tt为队头
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
            q[++tt] = x;
        }
        else if (op == "pop")
        {
            hh++;
        }
        else if (op == "empty")
        {
            if (hh > tt)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
        else
            cout << q[hh] << endl;
    }

    return 0;
}