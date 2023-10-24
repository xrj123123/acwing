/*
    求影响力的最大值最小，二分怨气值，假设当前怨气值为mid，将所有怨气值大于mid的两个点分别放入两个监狱，如果没有矛盾，
    即这些点构成的图是二分图，那么r = mid，否则l = mid + 1
*/

import java.io.*;
import java.util.Arrays;

public class J257 {
    static final int N = 20010, M = 200010;
    static int[] h = new int[N], e = new int[M], ne = new int[M], w = new int[M];
    static int[] color = new int[N];
    static int idx, n, m;

    static void add(int a, int b, int c) {
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static boolean check(int mid) {
        Arrays.fill(color, 0);
        for (int i = 1; i <= n; i++) {
            if (color[i] == 0) 
                if (!dfs(i, 1, mid))
                    return false;
        }
        return true;
    }

    static boolean dfs(int u, int c, int mid) {
        color[u] = c;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (w[i] <= mid)
                continue;
            if (color[j] == 0) {
                if (!dfs(j, 3 - c, mid))
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
            int c = Integer.parseInt(str[2]);
            add(a, b, c);
            add(b, a, c);
        }

        int l = 0, r = (int)1e9;
        while (l < r) {
            int mid = l + r >> 1;
            if (check(mid))
                r = mid;
            else
                l = mid + 1;
        }
        System.out.println(l);
    }
}