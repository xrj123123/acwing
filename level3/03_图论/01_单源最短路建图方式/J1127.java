import java.io.*;
import java.util.*;

public class J1127 {
    static final int N = 510, M = 810, C = 3000;
    static int[][] dist = new int[M][M];
    static int[] cows = new int[N];
    static boolean[] st = new boolean[M];
    static int[] h = new int[M], e = new int[C], ne = new int[C], w = new int[C];
    static int n, m, c, idx;

    public static void add(int a, int b, int c){
        e[idx] = b;
        ne[idx] = h[a];
        w[idx] = c;
        h[a] = idx++;
    }

    public static void spfa(int start) {
        Arrays.fill(dist[start], 1000);
        Arrays.fill(st, false);
        dist[start][start] = 0;
        Queue<Integer> q = new LinkedList<>();
        q.offer(start);
        st[start] = true;

        while (!q.isEmpty()) {
            int t = q.poll();
            st[t] = false;

            for (int i = h[t]; i != -1; i = ne[i]) {
                int u = e[i];
                if (dist[start][u] > dist[start][t] + w[i]) {
                    dist[start][u] = dist[start][t] + w[i];
                    if (!st[u]){
                        st[u] = true;
                        q.offer(u);
                    }
                }
            }
        }
    }
    
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
        c = Integer.parseInt(str[2]);

        for (int i = 1; i <= n; i++) 
            cows[i] = Integer.parseInt(br.readLine());
        
        Arrays.fill(h, -1);
        for (int i = 0; i < c; i++) {
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            int z = Integer.parseInt(str[2]);
            add(x, y, z);
            add(y, x, z);
        }

        for (int i = 1; i <= m; i++)
            spfa(i);

        int res = 0x3f3f3f3f;
        for (int i = 1; i <= m; i++){
            int t = 0;
            for (int j = 1; j <= n; j++) {
                t += dist[cows[j]][i];
            }
            res = Math.min(res, t);
        }
        System.out.println(res);
    }
}
