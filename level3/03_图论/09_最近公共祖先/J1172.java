import java.io.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class J1172 {
    static final int N = 40010, M = N * 2;
    static int[] h = new int[N], e = new int[M], ne = new int[M];
    static int[] depth = new int[N];
    static int[][] fa = new int[N][16];
    static int n, m, idx, root;

    static void add(int a, int b) {
        e[idx] = b;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static void bfs(int root) {
        Arrays.fill(depth, 0x3f3f3f3f);
        depth[0] = 0;
        depth[root] = 1;
        Queue<Integer> q = new LinkedList<>();
        q.offer(root);

        while (!q.isEmpty()) {
            int t = q.poll();

            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (depth[j] > depth[t] + 1) {
                    depth[j] = depth[t] + 1;
                    q.offer(j);
                    fa[j][0] = t;
                    for (int k = 1; k <= 15; k++)
                        fa[j][k] = fa[fa[j][k - 1]][k - 1];
                }
            }
        }
    }

    static int lca(int a, int b) {
        if (depth[a] < depth[b]) {
            int t = a;
            a = b;
            b = t;
        }

        for (int i = 15; i >= 0; i--) {
            if (depth[fa[a][i]] >= depth[b])
                a = fa[a][i];
        }
        if (a == b)
            return a;
        
        for (int i = 15; i >= 0; i--) {
            if (fa[a][i] != fa[b][i]) {
                a = fa[a][i];
                b = fa[b][i];
            }
        }

        return fa[a][0];
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(br.readLine());
        Arrays.fill(h, -1);
        for (int i = 0; i < n; i++) {
            String[] str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            if (b == -1)
                root = a;
            else {
                add(a, b);
                add(b, a);  
            }
        }

        bfs(root);

        m = Integer.parseInt(br.readLine());
        for (int i = 0; i < m; i++) {
            String[] str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            int z = lca(x, y);
            if (z == x)
                System.out.println(1);
            else if (z == y)
                System.out.println(2);
            else
                System.out.println(0);
        }
    }
}