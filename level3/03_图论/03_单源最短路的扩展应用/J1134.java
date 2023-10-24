/*
    最短路计数
    求最短路并且要求最短路的数量, 和背包问题求方案数类似, 先求出到某一点的最短路, 然后求出到该点的方案数 
    但是如果用dp来做, 需要满足拓扑图, 只有是拓扑图的时候才可以用dp来求
    因此可以建立一棵最短路树, 对于某一点x, 只有当他可以更新其他点时, 才去连一条边, 这样就是一个拓扑图
    求最短路的三种方案: bfs、Dijkstra、bellman_ford【spfa】
    bfs只入队一次, 只出队一次, 它的更新顺序是拓扑图, 出队的点不会在更新之前的点
    Dijkstra每个点只出队一次, 也可以看做是一个拓扑图, 每次出队的点是当前距离起点最近的点, 它只会更新后边的点,而不会更新之前的点
    bellman_ford【spfa】本身不具备拓扑性质, 因为每个点可以入队出队多次

    对于有负权边的图求方案数: 先用spfa跑一遍最短路, 然后建立拓扑树, 用dist[j] == dist[t] + 1判断, 如果满足, 就表示j可以由t更新而来, 就累加方案数
*/

import java.io.*;
import java.util.Arrays;
import java.util.*;

public class J1134 {
    static final int N = 100010, M = 400010, MOD = 100003;
    static int[] h = new int[N], e = new int[M], ne = new int[M];
    static int[] dist = new int[N], cnt = new int[N];
    static int n, m, idx;

    static void add(int a, int b){
        e[idx] = b;
        ne[idx] = h[a];
        h[a] = idx++; 
    }

    static void bfs(){
        Arrays.fill(dist, 0x3f3f3f3f);
        dist[1] = 0;
        cnt[1] = 1;
        Queue<Integer> q = new LinkedList<>();
        q.offer(1);

        while (!q.isEmpty()) {
            int t = q.poll();

            for (int i = h[t]; i != -1; i = ne[i]){
                int j = e[i];
                if (dist[j] > dist[t] + 1) {
                    dist[j] = dist[t] + 1;
                    cnt[j] = cnt[t];
                    q.offer(j);
                }else if (dist[j] == dist[t] + 1) {
                    cnt[j] = (cnt[j] + cnt[t]) % MOD;
                }
            }
        }
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);

        Arrays.fill(h, -1);
        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            add(x, y);
            add(y, x);
        }

        bfs();
        for (int i = 1; i <= n; i++)
            System.out.println(cnt[i]);
    }
}
