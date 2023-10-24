import java.io.*;
import java.util.*;

public class J1171 {
    static final int N = 10010, M = 2 * N;
    static int[] h = new int[N], e = new int[M], ne = new int[M], w = new int[M];
    static Map<Integer, List<PII>> query = new HashMap<>();
    static int[] p = new int[N], dist = new int[N], res = new int[M], st = new int[N];
    static int idx, n, m;

    static void add(int a, int b, int c) {
        e[idx] = b;
        ne[idx] = h[a];
        w[idx] = c;
        h[a] = idx++;
    }

    static int find(int x) {
        if (x != p[x])
            p[x] = find(p[x]);
        return p[x];
    }

    static void dfs(int u, int father) {
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (j == father)
                continue;
            dist[j] = dist[u] + w[i];
            dfs(j, u);
        }
    }

    static void tarjan(int u) {
        st[u] = 1;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (st[j] == 0) {
                tarjan(j);
                p[j] = u;
            }
        }

        if (query.containsKey(u)) {
            for (PII t : query.get(u)) {
                int y = t.first, idx = t.idx;
                if (st[y] == 2) {
                    int anc = find(y);
                    res[idx] = dist[u] + dist[y] - dist[anc] * 2;
                }
            }
        }
        st[u] = 2;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
        Arrays.fill(h, -1);
        for (int i = 0; i < N; i++)
            p[i] = i;

        for (int i = 0; i < n - 1; i++) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            int c = Integer.parseInt(str[2]);
            add(a, b, c);
            add(b, a, c);
        }

        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            if (!query.containsKey(x)) {
                query.put(x, new ArrayList<>());
            }
            if (!query.containsKey(y)) {
                query.put(y, new ArrayList<>());
            }
            query.get(x).add(new PII(y, i));
            query.get(y).add(new PII(x, i));
        }

        dfs(1, -1);
        tarjan(1);

        for (int i = 0; i < m; i++)
            System.out.println(res[i]);
    }
}

class PII {
    int first, idx;
    public PII(int first, int idx) {
        this.first = first;
        this.idx = idx;
    }
}
