#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(vector<int> a, vector<int> b)
{
    if (a.size() != b.size())
        return a.size() > b.size();

    for (int i = a.size() - 1; i >= 0; i--)
        if (a[i] != b[i])
            return a[i] - b[i];
    return true;
}

vector<int> add(vector<int> a, vector<int> b) 
{
    vector<int> c;
    int t = 0;
    int n = max(a.size(), b.size());
    for (int i = 0; i < n; i++)
    {
        if (i < a.size())
            t += a[i];
        if (i < b.size())
            t += b[i];
        c.push_back(t % 10);
        t /= 10;
    }
    if (t)
        c.push_back(t);
    return c;
}

vector<int> sub(vector<int> a, vector<int> b)
{
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); i++) 
    {   
        t += a[i];
        if (i < b.size())
            t -= b[i];
        c.push_back((t + 10) % 10);
        if (t < 0)
            t = -1;
        else 
            t = 0;
    }
    // 去掉前导0
    while(c.size() > 1 && c.back() == 0)
        c.pop_back();
    return c;
}

vector<int> mulsingal(vector<int> a, int b)
{
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); i++)
    {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    if (t) 
        c.push_back(t);
    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
    return c;
}

vector<int> mul(vector<int> a, vector<int> b) 
{
    vector<int> c(a.size() + b.size(), 0);
    for (int i = 0; i < b.size(); i++)
    {
        vector<int> temp = mulsingal(a, b[i]);
        for (int j = 0; j < i; j++)
            temp.insert(temp.begin(), 0);
        c = add(c, temp);
    }
    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
    return c;
}

void print(vector<int> a)
{
    for (int i = a.size() - 1; i >= 0; i--)
        cout << a[i];
    cout << endl; 
}

int main()
{
    string a, b;
    cin >> a >> b;
    vector<int> A, B;
    
    if (a[0] != '-' && b[0] != '-')
    {   
        for (int i = a.length() - 1; i >= 0; i--)
            A.push_back(a[i] - '0');
        for (int i = b.length() - 1; i >= 0; i--)
            B.push_back(b[i] - '0');
        auto c = add(A, B);
        print(c);
        if (cmp(A, B))
            c = sub(A, B);
        else
        {
            cout << "-";
            c = sub(B ,A);
        }
        print(c);
        c = mul(A, B);
        print(c);
    }else if(a[0] == '-' && b[0] == '-') 
    {
        for (int i = a.length() - 1; i >= 1; i--)
            A.push_back(a[i] - '0');
        for (int i = b.length() - 1; i >= 1; i--)
            B.push_back(b[i] - '0');
        auto c = add(A, B);
        cout << "-";
        print(c);

        if (cmp(A, B))
        {
            cout << "-";
            c = sub(A, B);
        }else
        {
            c = sub(B ,A);
        }
        print(c);

        c = mul(A, B);
        print(c);
    } else if(a[0] == '-' && b[0] != '-')
    {
        for (int i = a.length() - 1; i >= 1; i--)
            A.push_back(a[i] - '0');
        for (int i = b.length() - 1; i >= 0; i--)
            B.push_back(b[i] - '0');

        vector<int> c;
        if (cmp(A, B))
        {
            cout << "-";
            c = sub(A, B);
        }else
        {
            c = sub(B, A);
        }
        print(c);

        cout << "-";
        c = add(A, B);
        print(c);

        c = mul(A, B);
        cout << "-";
        print(c);
    } else if(a[0] != '-' && b[0] == '-')
    {
        for (int i = a.length() - 1; i >= 0; i--)
            A.push_back(a[i] - '0');
        for (int i = b.length() - 1; i >= 1; i--)
            B.push_back(b[i] - '0');

        vector<int> c;
        if (cmp(A, B))
            c = sub(A, B);
        else
        {
            cout << "-";
            c = sub(B, A);
        }
        print(c);

        c = add(A, B);
        print(c);

        c = mul(A, B);
        cout << "-";
        print(c);
    }
    
    return 0;
}