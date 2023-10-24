// acwing 148 合并果子
#include <iostream>
#include <queue>
using namespace std;
const int N = 1e4 + 10;
int a[N];
int n;

int main()
{
    cin >> n;
    priority_queue<int, vector<int>, greater<int> > heap;
    for(int i = 0; i< n; i++)
    {
        cin >> a[i];
        heap.push(a[i]);
    }
        
    int res = 0;
    while(heap.size() > 1)
    {
        int t = heap.top();
        heap.pop();
        t += heap.top();
        heap.pop();

        heap.push(t);
        res += t;
    }
    
    cout << res << endl;

    return 0;
}