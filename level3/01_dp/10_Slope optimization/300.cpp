#include <iostream>
#include <cstring>
typedef long long LL;
using namespace std;
const int N = 5010;
LL f[N];
int sumt[N], sumc[N];
int n, s;

int main()
{
    cin >> n >> s;
    for (int i = 1; i <= n; i++) 
    {
        int t, c;
        cin >> t >> c;
        sumt[i] = sumt[i - 1] + t;
        sumc[i] = sumc[i - 1] + c;
    }

    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            f[i] = min(f[i], f[j] + (LL)sumt[i] * (sumc[i] - sumc[j]) + s * (sumc[n] - sumc[j]));
        
    cout << f[n] << endl;

    return 0;
}