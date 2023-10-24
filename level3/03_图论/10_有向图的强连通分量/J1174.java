import java.io.*;
import java.util.Arrays;

public class J1174 {
    static final int N = 10010, M = 50010;
    static int[] h = new int[N], e = new int[M], ne = new int[M];
    static int[] dfn = new int[N], low = new int[N], stk = new int[N];
    static boolean[] in_stk = new boolean[N];
    static int scc_cnt;
    static int[] scc_size = new int[N], id = new int[N];
    static int[] cnt = new int[N];
    static int idx, top, timestamp, n, m;

    static void add(int a, int b) {
        e[idx] = b;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static void tarjan(int u){
        // 更新时间戳
        dfn[u] = low[u] = ++timestamp;
        // 当前点进栈
        stk[++top] = u;
        in_stk[u] = true;

        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dfn[j] == 0) {
                tarjan(j);
                low[u] = Math.min(low[u], low[j]);
            } else if (in_stk[j]) { // 点j在栈中，即前向边或横插边
                low[u] = Math.min(low[u], dfn[j]);
            }
        }

        // 点u是强连通分量最高点
        if (dfn[u] == low[u]) {
            // 强连通分量数+1
            ++scc_cnt;
            int y;
            // 将属于该强连通分量的所有元素从栈中弹出
            do {
                y = stk[top--];
                in_stk[y] = false;    
                id[y] = scc_cnt;
                scc_size[scc_cnt]++;    
            } while (y != u);
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
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            add(a, b);
        }

        for (int i = 1; i <= n; i++) {
            if (dfn[i] == 0)
                tarjan(i);
        }

        for (int u = 1; u <= n; u++) {
            for (int i = h[u]; i != -1; i = ne[i]) {
                int j = e[i];
                int a = id[u];
                int b = id[j];
                if (a != b) {
                    cnt[a]++;
                }
            }
        }

        int zeros = 0, res = 0;
        for (int i = 1; i <= scc_cnt; i++) {
            if (cnt[i] == 0) {
                res = scc_size[i];
                zeros++;
                if (zeros > 1) {
                    res = 0;
                    break;
                }
            }
        }
        System.out.println(res);
    }
}
