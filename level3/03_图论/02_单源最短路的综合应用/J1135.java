/*
    DFS + Dijkstra
    求的是从1号点出发，到其他5个点的最短距离，每次路径要经过这5个点
    首先暴力枚举所有情况，即5!=120种情况，例如当前是 1 3 2 5 4，先求从1走到3的最短路，然后求3到2的最短路，一直求到5到4的最短路，求5次
    总的时间复杂度为120*5*mlogn, mlogn是对优化版Dijkstra的时间复杂度，9.7*1e7, 可能会tle

    因此我们可以改变一下顺序，先求出每个点到其他点的最短路，然后dfs枚举每种情况，这样时间复杂度就降为mlogn + 5!
*/

import java.io.*;
import java.util.Arrays;
import java.util.PriorityQueue;

public class J1135 {
    static final int N = 50010, M = 200010;
    static int[][] dist = new int[6][N];  // dist[i]表示从i到其他点的距离
    static int[] source = new int[6];
    static int[] h = new int[N], e = new int[M], w = new int[M], ne = new int[M];
    static boolean[] st = new boolean[N];
    static int n, m, res, idx;

    public static void add(int a, int b, int c){
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    public static void Dijkstra(int start, int[] dist){
        PriorityQueue<PII> q = new PriorityQueue<>((o1, o2) -> o1.x - o2.x);
        Arrays.fill(dist, 0x3f3f3f3f);
        Arrays.fill(st, false);
        q.offer(new PII(0, start));
        dist[start] = 0;

        while (!q.isEmpty()) {
            PII t = q.poll();
            int ver = t.y;
            if (st[ver]) 
                continue;
            st[ver] = true;

            for (int i = h[ver]; i != -1; i = ne[i]) {
                int u = e[i];
                if (dist[u] > t.x + w[i]){
                    dist[u] = t.x + w[i];
                    q.offer(new PII(dist[u], u));
                }
            }
        }
    }

    // 当前搜了u个，当前在now，总距离为distence
    public static void dfs(int u, int now, int distence) {
        if (u == 5){
            res = Math.min(res, distence);
            return;
        }
        for (int i = 1; i <= 5; i++) {
            if (!st[i]){
                st[i] = true;
                dfs(u + 1, i, distence + dist[now][source[i]]);
                st[i] = false;
            }
        }
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);

        str = br.readLine().split(" ");
        source[0] = 1;
        for (int i = 0; i < 5; i++) 
            source[i + 1] = Integer.parseInt(str[i]);
        
        Arrays.fill(h, -1);

        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            int t = Integer.parseInt(str[2]);
            add(x, y, t);
            add(y, x, t);
        }

        for (int i = 0; i <= 5; i++) {
            Dijkstra(source[i], dist[i]);
        }
        
        Arrays.fill(st, false);
        res = 0x3f3f3f3f;
        dfs(0, 0, 0);
        System.out.println(res);
    }
}

class PII{
    int x; 
    int y;
    public PII(int x, int y){
        this.x = x;
        this.y = y;
    }
}
