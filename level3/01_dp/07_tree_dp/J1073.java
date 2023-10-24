import java.util.Scanner;
import java.util.Arrays;;

public class J1073 {
    static int N = 10010, M = N * 2, INF = 0x3f3f3f3f;
    static int[] h = new int[N], e = new int[M], ne = new int[M], w = new int[M];
    static int[] d1 = new int[N], d2 = new int[N], p1 = new int[N], p2 = new int[N], up = new int[N];
    static int idx, n;

    public static void add(int a, int b, int c){
        e[idx] = b;
        ne[idx] = h[a];
        w[idx] = c;
        h[a] = idx++;
    }

    public static int dfs_d(int u, int father){
        for (int i = h[u]; i != -1; i = ne[i]){
            int j = e[i];
            if (j == father) continue;
            int d = dfs_d(j, u) + w[i];
            if (d > d1[u]){
                d2[u] = d1[u]; 
                p2[u] = p1[u];
                d1[u] = d;
                p1[u] = j;
            }else if (d > d2[u]){
                d2[u] = d;
                p2[u] = j;
            }
        }
        return d1[u];
    }

    public static void dfs_u(int u, int father){
        for (int i = h[u]; i != -1; i = ne[i]){
            int j = e[i];
            if (j == father) continue;
            if (p1[u] == j) up[j] = w[i] + Math.max(up[u], d2[u]);
            else up[j] = w[i] + Math.max(up[u], d1[u]);
            dfs_u(j, u);
        }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        Arrays.fill(h, -1);
        for (int i = 1; i < n; i++){
            int a = sc.nextInt(), b = sc.nextInt(), c = sc.nextInt();
            add(a, b, c);
            add(b, a, c);
        }

        dfs_d(1, -1);
        dfs_u(1, -1);

        int res = INF;
        for (int i = 1; i <= n; i++){
            res = Math.min(res, Math.max(up[i], d1[i]));
        }
        System.out.println(res);
        sc.close();
    }
    
}
