// acwing 129 火车进栈
/*
每辆火车有3种状态，1.未进站 2.在站中 3.出站
对于在站中的火车，优先让他出站(按字典序),若出站车辆达到n，则输出
若有未进站车辆，则进站
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int n;
int now = 1, cnt; // now为当前第几辆车，cnt为合法数量，达到20停止
stack<int> in;    // 在车站中的车辆
vector<int> post; // 出站的车辆

void dfs()
{
    if (cnt == 20)
        return;

    if (post.size() == n) // 出站的火车达到n辆，输出
    {
        for (int t : post)
            printf("%d", t);
        puts("");
        cnt++;
    }

    if (in.size()) // 如果车站内有车，优先出站
    {
        post.push_back(in.top());
        in.pop();
        dfs();
        in.push(post.back());
        post.pop_back();
    }

    if (now <= n)
    {
        in.push(now++);
        dfs();
        in.pop();
        now--;
    }
}

int main()
{
    cin >> n;

    dfs();

    return 0;
}
