// acwing 1012 友好城市
/*
    先将南北一边按升序排好序，然后求另一边的最长上升子序列
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5010;
int n, f[N];
struct node
{
    int north;
    int sourth;
    bool operator < (const node &W) const
    {
        return north < W.north;
    }
}point[N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &point[i].sourth, &point[i].north);
    
    sort(point + 1, point + n + 1);

    for (int i = 1; i <= n; i++)
    {
        f[i] = 1;
        for (int j = 1; j < i; j++)
            if (point[i].sourth > point[j].sourth)
                f[i] = max(f[i], f[j] + 1);
    }

    int res = 0;
    for (int i = 1; i <= n; i++)
        res = max(res, f[i]);
    
    cout << res << endl;

    return 0;
}
