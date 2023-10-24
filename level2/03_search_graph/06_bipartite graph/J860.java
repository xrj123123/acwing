import java.io.*;
import java.util.Arrays;

public class J860 {
    static final int N = 100010, M = 2 * N;
    static int[] h = new int[N], e = new int[M], ne = new int[M];
    static int[] color = new int[N];
    static int idx, n, m;

    static void add(int a, int b) {
        e[idx] = b;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static boolean dfs(int u, int c) {
        color[u] = c;

        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (color[j] == 0) {
                if (!dfs(j, 3 - c))
                    return false;
            } else if (color[j] == c)
                return false;
        }

        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
        Arrays.fill(h, -1);
        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            add(a, b);
            add(b, a);
        }

        boolean flag = true;
        for (int i = 1; i <= n; i++) {
            if (color[i] == 0) {
                if (!dfs(i, 1)) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag)
            System.out.println("Yes");
        else
            System.out.println("No");
    }
}
