import java.io.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class J1129 {
    static final int N = 2510, M = 6200 * 2 + 10;
    static int[] h = new int[N], e = new int[M], w = new int[M], ne = new int[M];
    static int[] dist = new int[N];
    static boolean[] st = new boolean[N];
    static int n, m, s, t, idx;

    public static void add(int a, int b, int c) {
        e[idx] = b;
        ne[idx] = h[a];
        w[idx] = c;
        h[a] = idx++;
    }

    public static void spfa(){
        Arrays.fill(dist, 0x3f3f3f3f);
        dist[s] = 0;
        Queue<Integer> q = new LinkedList<>();
        q.offer(s);
        st[s] = true;

        while (!q.isEmpty()) {
            int t = q.poll();
            st[t] = false;

            for (int i = h[t]; i != -1; i = ne[i]) {
                int u = e[i];
                if (dist[u] > dist[t] + w[i]){
                    dist[u] = Math.min(dist[u], dist[t] + w[i]);
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
        s = Integer.parseInt(str[2]);
        t = Integer.parseInt(str[3]);

        Arrays.fill(h, -1);
        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]), b = Integer.parseInt(str[1]), c = Integer.parseInt(str[2]);
            add(a, b, c);
            add(b, a, c);
        }

        spfa();
        System.out.println(dist[t]);
    }
}
