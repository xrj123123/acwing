// 常用STL容器
/*
vector  变长数组，倍增的思想
    a.size();   返回a的大小，所有容器都有，时间复杂度为O1
    a.empty();  返回a是不是空的，所有容器都有，时间复杂度为O1
    a.clear();  清空容器
    front()/back()  返回第一个数/最后一个数
    push_back()/pop_back(): 在最后插入一个数/删除最后一个数
    begin()/end()   迭代器，vector的第一个数/vector的最后一个数的后一个数
    erase(l,r)      删除l到r之间元素
    []
    支持比较运算(字典序)

pair<int,int>   存储一个二元组，两个变量可以任意
    pair<string,int> p;
    p.first();   p的第一个元素
    p.second();  p的第二个元素
    支持比较运算，以first为第一关键字，以second为第二关键字(字典序)

string  字符串
    size()/length()
    empty()
    clear()
    substr(a,b)     返回从下标a开始，长度为b的子串
    c_str()         返回字符数组的起始地址

queue
    size()
    empty()
    push()      向队尾插入一个元素
    front()     返回队头元素
    pop()       弹出队头元素
    back()      返回队尾元素

queue_priority,优先队列，实现原理是堆，默认大根堆
    push()      插入一个元素
    top()       返回队头元素
    pop()       弹出队头元素
    实现小根堆：
            1.插入时插入负值
            2.priority_queue<int,vector<int>,greater<int>> heap;

stack   栈，
    size()
    empty()
    push()      向栈顶插入一个元素
    top()       返回栈顶元素
    pop()       弹出栈顶元素

deque   双端队列    效率低
    size()
    empty()
    clear()
    front()
    back()
    push_back()
    pop_back()
    push_front()
    pop_front()
    begin()/end()
    []

set map  multiset  multimap 基于平衡二叉树(红黑树)，动态维护有序序列
    size()
    empty()
    clear()
    begin()/end()   ++,-- 返回前驱和后继  O(logn)

    set/multiset
        set中不能有重复元素，multiset可以有重复元素
        insert()    插入一个数  O(logn)
        find()      查找一个数，不存在返回end迭代器
        count()     返回某一个数的个数
        erase()
            1.输入是一个数x，删除所有x      O(k+logn),k是x的个数
            2.输入是一个迭代器，删除这个迭代器
        lower_bound()/upper_bound()
            lower_bound():返回>=x的最小数的迭代器，不存在返回end
            upper_bound():返回>x的最小数的迭代器，不存在返回end

    map/multimap
        insert()    插入的数是一个pair
        erase()     输入的参数是pair或者迭代器
        find()      查找一个数，不存在返回end迭代器
        []          O(logn)
        lower_bound()/upper_bound()


unordered_set  unordered_map  unordered_multiset  unordered_multimap    哈希表
    和上面类似，增删改查时间复杂度为O(1)
    不支持lower_bound()/upper_bound(),迭代器的++,-- , 因为内部是无序的


bitset  压位     
    bitset<10000> s;    长度为10000的bitset
    ~s,&,|,^            取反/与/或/异或
    >>,<<
    ==,!=
    []
    count()             返回有多少个1
    any()               判断是否至少有一个1
    none()              判断是否全为0
    set()               把所有位置位1
    set(k,v)            将第k位变为1
    reset()             把所有位变为0
    flip()              等价于~s
    flip(k)             把第k位取反
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
using namespace std;
int main()
{
    cout << "vector------------" << endl;
    vector<int> a;        // 定义一个vector
    vector<int> b(10);    // 定义一个长度为10的vector
    vector<int> c(10, 3); //定义一个长度为10的vector,每个元素都是3
    vector<int> d[10];    // 定义一个vector数组，10个vector

    for (int i = 0; i < 10; i++)
        a.push_back(i);

    for (int i = 0; i < a.size(); i++)
        cout << a[i] << " ";
    cout << endl;

    for (vector<int>::iterator i = a.begin(); i != a.end(); i++)
        cout << *i << " ";
    cout << endl;

    for (auto i = a.begin(); i != a.end(); i++)
        cout << *i << " ";
    cout << endl;

    for (auto x : a)
        cout << x << " ";
    cout << endl;

    cout << "pair-------------" << endl;
    pair<int, string> p;
    // 初始化的两种方式
    p = make_pair(10, "xrj");
    p = {20, "abc"};
    cout << p.first << " " << p.second << endl;

    pair<int, pair<int, int>> p1;
    p1 = {1, {2, 3}};
    cout << p1.first << " " << p1.second.first << " " << p1.second.second << endl;

    cout << "string------------" << endl;
    string aa = "xrj";
    aa += "def";
    cout << aa << endl;
    cout << aa.substr(1, 2) << endl; // 从下标1开始，反正长度为2的子串，长度超过的话，输出到最后一个字符
    cout << aa.substr(1) << endl;
    printf("%s\n", aa.c_str());

    cout << "queue---------------" << endl;
    queue<int> q;

    cout << "queue_priority-------" << endl;
    priority_queue<int> heap; // 大根堆
    for (int i = 0; i < 10; i++)
        heap.push(i);
    cout << heap.top() << endl;

    priority_queue<int, vector<int>, greater<int>> heap1; // 小根堆
    for (int i = 0; i < 10; i++)
        heap1.push(i);
    cout << heap1.top() << endl;

    cout << "map---------------" << endl;
    map<string, int> m;
    m["xrj"] = 1;
    cout << m["xrj"] << endl;

    return 0;
}