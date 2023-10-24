// acwing 240 食物链
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
// 用并查集来维护每个动物到根节点的距离，距离模0，和根节点同类，模1，吃根节点，模2，被根节点吃
int p[N], d[N]; // d[i]表示第i个动物到根节点的距离

int find(int x)
{
    if (x != p[x])
    {
        int t = find(p[x]); // 根节点
        d[x] += d[p[x]];    // 距离从到父节点的距离更新为到根节点的距离，加上父节点到根节点距离即可
        p[x] = t;
    }
    return p[x];
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        p[i] = i;

    int res = 0;
    while (k--)
    {
        int k, x, y;
        scanf("%d%d%d", &k, &x, &y);
        int px = find(x), py = find(y);
        if (x > n || y > n)
            res++;
        else if (k == 1) // x和y同类
        {
            if (px == py && (d[x] - d[y]) % 3) // x和y在一个集合且x和y到根节点距离不一样
                res++;
            else if (px != py) // x和y不在一个集合
            {
                p[px] = py;          // 让px归到py中
                d[px] = d[y] - d[x]; // 因为x到px的距离为d[x],y到py的距离为d[y],且同类，d[x]+d[px]=d[y]
            }
        }
        else if (k == 2) // x吃y，即x到根节点距离比y大一
        {
            if (px == py && (d[x] - d[y] - 1) % 3) // 在同一个集合，但d[x]不比d[x]大1
                res++;
            else if (px != py) // 不在一个集合
            {
                p[px] = py;
                d[px] = d[y] - d[x] + 1; // d[x]+d[px]=d[y]+1
            }
        }
    }
    printf("%d\n", res);

    return 0;
}