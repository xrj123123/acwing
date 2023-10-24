// acwing 845 八数码
/*
    12345678x是最终状态，将初试状态加入队列，然后每次取出队头状态，扩展其状态并加入队列
    用一个unordermap<string,int>来存储该状态离初始状态的距离
*/
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

int bfs(string start)
{
    queue<string> q;
    unordered_map<string, int> d;
    q.push(start);
    d[start] = 0;
    string end = "12345678x";

    while (q.size())
    {
        auto t = q.front();
        q.pop();
        int dis = d[t]; // 当前点距离起点的距离
        if (t == end)
            return dis;

        int idx = t.find('x');        // 返回x的下标
        int x = idx / 3, y = idx % 3; // x的横纵坐标
        for (int i = 0; i < 4; i++)
        {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3)
            {
                swap(t[a * 3 + b], t[idx]);
                if (!d.count(t))    // 如果d中没有出现t这种状态，那么入队
                {
                    d[t] = dis + 1;
                    q.push(t);
                }
                swap(t[a * 3 + b], t[idx]);
            }
        }
    }

    return -1;
}

int main()
{
    string start;
    for (int i = 0; i < 9; i++)
    {
        char s;
        cin >> s;
        start += s;
    }

    cout << bfs(start) << endl;

    return 0;
}
