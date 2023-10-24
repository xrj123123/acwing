import java.io.*;
import java.util.*;

public class J904 {
    static final int N = 510, M = 5210;
    static int[] h = new int[N], e = new int[M], ne = new int[M], w = new int[M];
    static int[] dist = new int[N], cnt = new int[N];
    static boolean[] st = new boolean[N];
    static int n, m, k, idx;

    static void add(int a, int b, int c) {
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static boolean spfa(){
        Queue<Integer> q = new LinkedList<>();
        for (int i = 1; i <= n; i++) {
            q.offer(i);
            st[i] = true;
        }

        while (!q.isEmpty()) {
            int u = q.poll();
            st[u] = false;

            for (int i = h[u]; i != -1; i = ne[i]) {
                int j = e[i];
                if (dist[j] > dist[u] + w[i]) {
                    dist[j] = dist[u] + w[i];
                    cnt[j] = cnt[u] + 1;
                    if (cnt[j] >= n)
                        return true;
                    if (!st[j]){
                        q.offer(j);
                        st[j] = true;
                    }
                        
                }
            }
        }
        return false;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int t = Integer.parseInt(br.readLine());
        for (int cases = 0; cases < t; cases++){
            idx = 0;
            Arrays.fill(h, -1);
            Arrays.fill(dist, 0);
            Arrays.fill(cnt, 0);
            Arrays.fill(st, false);

            String[] str = br.readLine().split(" ");
            n = Integer.parseInt(str[0]);
            m = Integer.parseInt(str[1]);
            k = Integer.parseInt(str[2]);

            for (int i = 0; i < m; i++) {
                str = br.readLine().split(" ");
                int a = Integer.parseInt(str[0]);
                int b = Integer.parseInt(str[1]);
                int c = Integer.parseInt(str[2]);
                add(a, b, c);
                add(b, a, c);
            }

            for (int i = 0; i < k; i++) {
                str = br.readLine().split(" ");
                int a = Integer.parseInt(str[0]);
                int b = Integer.parseInt(str[1]);
                int c = Integer.parseInt(str[2]);
                add(a, b, -c);
            }

            if (spfa())
                System.out.println("YES");
            else
                System.out.println("NO");

        }

    }
}
