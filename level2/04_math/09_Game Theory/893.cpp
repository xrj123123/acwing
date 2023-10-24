// acwing 893 集合-Nim游戏
/*
    Mex运算:
        设S表示一个非负整数集合。定义mex(S)为求出不属于集合S的最小非负整数的运算，即:
        mex(S) = min(x),x属于自然数,且x不属于S

    SG函数:
        在有向图游戏中，对于每个节点x，设从x出发共有k条有向边，分别到达节点y1、y2...yk，定义SG(x)为x的后继节点
        y1、y2、...yk的SG函数值构成的集合在执行mex(S)运算的结果，即:
            SG(x) = mex({SG(y1)、SG(y2)...SG(yk)})
        特别的，整个有向图游戏G的SG函数值被定义为有向图游戏起点s的SG函数值，即SG(G)=SG(s)

    定义终点的SG，SG(终点)=0
    某一个状态x的SG值，x可以到达的状态有y1、y2、y3...yk，SG(x)=mex{SG(y1),SG(y2),SG(y3),...SG(yk)}
    例如A->B, A->C  B=0,C=1, 则SG(A)=2

    必胜状态:SG(x)≠0, 任走一步都可以到达0状态(如果到不了，SG(x)就为0)
    必败状态:SG(x)=0 (终点状态为0)

    如果有n个图，那么
        必胜状态:SG(x1)^SG(x2)...^SG(xn) ≠ 0
        必败状态:SG(x1)^SG(x2)...^SG(xn) = 0
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <unordered_set>
using namespace std;
const int N = 110, M = 1e5 + 10;
int n, m;
int s[N], f[M]; // s表示集合S中的数字，f[i]表示第i个点的SG值

// 返回点x的SG值
int sg(int x)
{
    if (f[x] != -1)
        return f[x];
    unordered_set<int> S;
    for (int i = 0; i < m; i++)
    {
        int sum = s[i];
        if (x >= sum)
            S.insert(sg(x - sum));
    }

    for (int i = 0;; i++)
        if (!S.count(i))
            return f[x] = i;
}

int main()
{
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> s[i];
    cin >> n;
    int res = 0;
    memset(f, -1, sizeof f);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        res = res ^ sg(x);
    }

    if (res)
        puts("Yes");
    else
        puts("No");

    return 0;
}
