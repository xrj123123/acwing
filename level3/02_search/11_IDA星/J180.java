/*
    IDA*
    IDA*算法是在迭代加深的基础上，增加了一个预估函数。
    假设当前最大深度为depth，当前搜索到了k层，k+f(k) > depth，就退出, f(k)是当前状态的估价函数，且f(k) <= g(k),预估值小于等于真实值

    本题中，直接DFS搜索: 设一次移动i本书，那么有n-i+1种移动方式，可以放的位置有n-i个(去除本身的位置)
    i从1枚举到n，全部情况就是∑(n-i+1)*(n-i) 1<=i<=n, 题目中n的范围是15，去掉重复情况(每种情况会出现两次), 每次搜索就会有560种情况
    最多搜索四层，也就是560^4, 显然超时。因此可以使用IDA*来做

    估价函数的设计，在排好序的情况下，每个数字和它的后继值相差1，每次移动有三个数字的后继会被改变，假设当前序列不正确的后继数为tot，每次最多改变3个
    因此至少需要tot/3(上取整)步可以排好序，所以估价函数可以定义为(tot+2)/3, 如果当前层数+(tot+2)/3 > depth，就退出
 */

import java.io.*;
import java.util.Arrays;

public class J180 {
    static final int N = 15;
    static int[][] w = new int[5][N];
    static int[] q = new int[N];
    static int n;

    public static int f(){
        int tot = 0;
        for (int i = 0; i + 1 < n; i++)
            if (q[i + 1] - q[i] != 1)
                tot++;
        return (tot + 2) / 3;
    }

    public static boolean dfs(int u, int depth) {
        if (u + f() > depth) return false;
        if (f() == 0) return true;

        for (int len = 1; len < n; len++)
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                for (int k = r + 1; k < n; k++) {
                    w[u] = Arrays.copyOf(q, q.length);
                    int y = l;
                    for (int x = r + 1; x <= k; x++, y++) q[y] = w[u][x];
                    for (int x = l; x <= r; x++, y++) q[y] = w[u][x];
                    if (dfs(u + 1, depth)) return true;
                    q = Arrays.copyOf(w[u], w[u].length);
                }
            }

        return false;
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());
        while (T-- > 0) {
            n = Integer.parseInt(br.readLine());
            String str[] = br.readLine().split(" ");
            for (int i = 0; i < n; i++)
                q[i] = Integer.parseInt(str[i]);
        
            int depth = 0;
            while (depth < 5 && !dfs(0, depth)) depth++;

            if (depth == 5) 
                System.out.println("5 or more");
            else
                System.out.println(depth);
        }
    }
}