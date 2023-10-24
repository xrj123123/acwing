import java.io.*;
import java.util.*;

public class J1128 {
    static final int N = 110, M = 410;
    static int[] dist = new int[N];
    static int[] h = new int[N], e = new int[M], ne = new int[M], w = new int[M];
    static boolean[] st = new boolean[N];
    static int n, m, idx;

    public static void add(int a, int b, int c) {
        e[idx] = b;
        ne[idx] = h[a];
        w[idx] = c;
        h[a] = idx++;
    }

    public static void spfa(){
        Arrays.fill(dist, 0x3f3f3f3f);
        dist[1] = 0;
        Queue<Integer> q = new LinkedList<>();
        q.offer(1);
        st[1] = true;

        while (!q.isEmpty()) {
            int t = q.poll();
            st[t] = false;

            for (int i = h[t]; i != -1; i = ne[i]) {
                int u = e[i];
                if (dist[u] > dist[t] + w[i]) {
                    dist[u] = dist[t] + w[i];
                    if (!st[u]) {
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

        Arrays.fill(h, -1);
        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            int z = Integer.parseInt(str[2]);
            add(x, y, z);
            add(y, x, z);
        }

        spfa();
        int res = 0;
        for (int i = 1; i <= n; i++)
            res = Math.max(res, dist[i]);

        if (res == 0x3f3f3f3f)
            System.out.println(-1);
        else
            System.out.println(res);
    }
}
