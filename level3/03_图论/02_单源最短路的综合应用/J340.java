/*
    二分 + 双端队列广搜
    题目中要求的是在一条路径中第k+1大的花费，要求是花费最少，也就是求最大值最小，可以使用二分
    二分枚举最小花费，假设当前花费为x，如果从1到N的路径上大于x的路径数小于等于k，则x满足条件
    如果从1到N的路径上大于x的路径数大于k，则不满足【因为当前x就不是最小花费了】
    二分的起点和终点要设置为0和1e6+1，起点设置为0是因为可能路径上的路径数小于等于k，因此花费为0.
    终点设置为1e6+1，是因为路径长度最大为1e6, 假设1和N无法连通，那么二分的答案一定会枚举到1e6+1，此时可以判断无解
    如果设置为1e6, 无解的情况会返回1e6, 有解的情况也会返回1e6
    对于二分出来的每种答案，如何找到最短路径中大于x的路径数，我们可以将大于x的路径权值设为1，小于等于x的路径权值设为0，
    最终从1到n的路径长度即为大于x的路径数, 这样设置后，路径权值只有0和1，因此可以使用双端队列广搜
*/

import java.io.*;
import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;

public class J340 {
    static final int N = 1010, M = 20010;
    static int[] dist = new int[N];
    static boolean[] st = new boolean[N];
    static int[] h = new int[N], e = new int[M], ne = new int[M], w = new int[M];
    static int n, p, k, idx;

    public static void add(int a, int b, int c){
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    public static boolean check(int x){
        Arrays.fill(dist, 0x3f3f3f3f);
        Arrays.fill(st, false);
        Deque<Integer> q = new LinkedList<>();
        dist[1] = 0;
        q.offerLast(1);

        while (!q.isEmpty()) {
            int t = q.pollFirst();
            if (st[t]) continue;
            st[t] = true;

            for (int i = h[t]; i != -1; i = ne[i]){
                int u = e[i];
                int v = w[i] > x ? 1 : 0;
                if (dist[u] > dist[t] + v) {
                    dist[u] = dist[t] + v;
                    if (v == 0)
                        q.offerFirst(u);
                    else
                        q.offerLast(u);
                }
            }
        }

        return dist[n] <= k;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        p = Integer.parseInt(str[1]);
        k = Integer.parseInt(str[2]);

        Arrays.fill(h, -1);

        while (p-- > 0) {
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            int z = Integer.parseInt(str[2]);
            add(x, y, z);
            add(y, x, z);
        }
        
        int l = 0, r = (int)1e6 + 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (check(mid))
                r = mid;
            else
                l = mid + 1;
        }
        if (l == (int)1e6 + 1)
            System.out.println(-1);
        else
            System.out.println(l);
    }
}
