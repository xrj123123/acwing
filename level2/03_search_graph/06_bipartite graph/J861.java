import java.io.*;
import java.util.Arrays;

public class J861 {
    static final int N = 510, M = 100010;
    static int[] h = new int[N], e = new int[M], ne = new int[M];
    static int[] match = new int[N];    // match[i] = j表示女生i匹配的男生j
    static boolean[] st = new boolean[N]; // st[i]表示这一轮中女生i是否被匹配过
    static int idx, n1, n2, m;

    static void add(int a, int b) {
        e[idx] = b;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static boolean find(int u) {
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (!st[j]) {
                st[j] = true;
                if (match[j] == 0 || find(match[j])) {
                    match[j] = u;
                    return true;
                }
            }
        }
        return false;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n1 = Integer.parseInt(str[0]);
        n2 = Integer.parseInt(str[1]);
        m = Integer.parseInt(str[2]);
        Arrays.fill(h, -1);
        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            add(a, b);
        }

        int res = 0;
        for (int i = 1; i <= n1; i++) {
            Arrays.fill(st, false);
            if (find(i))
                res++;
        }
        System.out.println(res);
    }
}
