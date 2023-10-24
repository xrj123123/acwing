/*
    A*算法
    题目说明了点和边可以重复走，因此可以存在环，并且求的是第K短边，也就是终点第K次出队时的长度，所以对于一个点来说，他需要将他所有临边全部入队
    如果S == T，需要K++，因为题目要求最少含有一条边，起点终点相同就是0条边，应该从第二短开始算

    这里估价函数用当前到到终点最短距离来计算，直接反向dijkstra一遍
    在A*算法中，用一个cnt数组表示每个点出队几次，这里需要注意，终点出队K次说明终点时第K短边，但是如果中间的点出队K次并不能满足他是第K短
    而在入队时，当某个点入队此时cnt[j]>=K就不在入队是因为: 点j已经出队K次了，还没有找到终点的第K短边
    说明从j出发找不到第k短路(让终点出队k次)，即继续让j入队的话依然无解，那么就没必要让j继续入队了
    tle数据如下
    4 4
    1 2 1
    1 3 1
    3 4 1
    4 3 1
    1 2 2
 */

import java.io.*;
import java.util.*;

public class J178 {
    static final int N = 1010, M = 20010;
    static int n, m, S, T, K, idx;
    static int[] h = new int[N], rh = new int[N], e = new int[M], ne = new int[M], w = new int[M];
    static int[] dist = new int[N], cnt = new int[N];
    static boolean[] st = new boolean[N];
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
        Arrays.fill(h, -1);
        Arrays.fill(rh, -1);
        for (int i = 0; i < m ; i++) {
            int a, b, c;
            str = br.readLine().split(" ");
            a = Integer.parseInt(str[0]); b = Integer.parseInt(str[1]); c = Integer.parseInt(str[2]);
            add(h, a, b, c);
            add(rh, b, a, c);
        }

        str = br.readLine().split(" ");
        S = Integer.parseInt(str[0]); T = Integer.parseInt(str[1]); K = Integer.parseInt(str[2]);
        if (S == T) K++;

        dijkstra();
        System.out.println(a_star());
    }

    public static void add(int[] h, int a, int b, int c){
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    public static void dijkstra(){
        PriorityQueue<PII> q = new PriorityQueue<>(new Comparator<PII>() {
            @Override
            public int compare(PII p1, PII p2) {
                return p1.x - p2.x;
            }
        });
        Arrays.fill(dist, 0x3f3f3f3f);
        q.offer(new PII(0, T));
        dist[T] = 0;

        while (!q.isEmpty()) {
            PII t = q.poll();
            int ver = t.y;
            st[ver] = true;

            for (int i = rh[ver]; i != -1; i = ne[i]) {
                int j = e[i];
                if (st[j]) continue;
                if (dist[j] > dist[ver] + w[i]) {
                    dist[j] = dist[ver] + w[i];
                    q.offer(new PII(dist[j], j));
                }
            }
        }
    }

    public static int a_star(){
        PriorityQueue<PIII> q = new PriorityQueue<>(new Comparator<PIII>(){
            @Override
            public int compare(PIII p1, PIII p2) {
                return p1.x - p2.x;
            }
        });
        q.offer(new PIII(dist[S], new PII(0, S)));

        while (!q.isEmpty()) {
            PIII t = q.poll();
            int ver = t.p.y;
            int dis = t.p.x;

            cnt[ver]++;
            if (cnt[T] == K) return dis;

            for (int i = h[ver]; i != -1; i = ne[i]) {
                int j = e[i];
                if (cnt[j] < K)
                    q.offer(new PIII(dis + w[i] + dist[j], new PII(dis + w[i], j)));
            }
        }
        return -1;
    }
}

class PII {
    int x;
    int y;
    public PII(int x, int y){
        this.x = x;
        this.y = y;
    }
}

class PIII{
    int x;
    PII p;
    public PIII(int x, PII p) {
        this.x = x;
        this.p = p;
    }
}