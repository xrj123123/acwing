/*
    每个学校看做一个点，应援看做边，建立一个有向图。我们先使用tarjan算法对图中强联通分量缩点，然后形成拓扑图，入度为0的点的个数就是第一问的答案。
    如果我们不使用tarjan缩点，而是直接求入度为0的点的个数的话，那么如果该图是一个强联通分量，即一个环，所有点的入度都不为0，结果为0
    但是根据题目要求我们仍然需要将软件提供给某一个学校才可以，在使用tarjan后会将这个环缩为一个点，这样该点入度为0，就是正确答案

    第二问的要求是任意一个点都可以到达其他所有点，即将当前图变为一个强联通分量至少需要添加多少条边
    设入度为0的点为集合P，出度为0的点为集合Q，答案为max(|P|,|Q|)。如果当前图已经是一个强联通分量，答案为0

    证明：假设|P|<=|Q|
        当|P|==1，此时终点Q的数量大于等于1，如果想要形成强联通分量，那么所有的终点都必须连一条向起点P的边，此时，需要边的数量为|Q|
        当|P|>1，此时|Q|>=|P|>1，那么至少存在两个起点p1, p2和两个终点q1, q2，其中p1--->q1，p2--->q2，此时我们添加一条从q1--->p2的边，
        添加完成后，|P'|=|P|-1，|Q'|=|Q|-1，以此类推，我们一直这样添加边，直到|P'|=1，那么一共添加了|P|-1条边，此时起点只有一个点，
        想要形成强联通分量，还需要添加|Q'|条边，|Q'|=|Q|-（|P|—1)，|Q'|+|P|-1 = |Q|
*/

import java.io.*;
import java.util.Arrays;

public class J367 {
    static final int N = 110, M = 10010;
    static int[] h = new int[N], e = new int[M], ne = new int[M];
    static int[] dfn = new int[N], low = new int[N], stk = new int[N];
    static boolean[] in_stk = new boolean[N];
    static int[] id = new int[N];
    static int[] din = new int[N], dout = new int[N];
    static int idx, top, scc_cnt, timestamp, n;

    static void add(int a, int b) {
        e[idx] = b;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static void tarjan(int u) {
        dfn[u] = low[u] = ++timestamp;
        stk[++top] = u;
        in_stk[u] = true;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dfn[j] == 0) {
                tarjan(j);
                low[u] = Math.min(low[u], low[j]);
            } else if (in_stk[j]) {
                low[u] = Math.min(low[u], dfn[j]);
            }
        }

        if (dfn[u] == low[u]) {
            ++scc_cnt;
            int y;
            do {
                y = stk[top--];
                in_stk[y] = false;
                id[y] = scc_cnt;
            } while(y != u);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Arrays.fill(h, -1);
        n = Integer.parseInt(br.readLine());
        
        for (int i = 1; i <= n; i++) {
            String[] str = br.readLine().split(" ");
            for (int j = 0; j < str.length - 1; j++) {
                int a = Integer.parseInt(str[j]);
                add(i, a);
            }
        }

        for (int i = 1; i <= n; i++) 
            if (dfn[i] == 0)
                tarjan(i);

        for (int u = 1; u <= n; u++) {
            for (int i = h[u]; i != -1; i = ne[i]) {
                int j = e[i];
                int a = id[u], b = id[j];
                if (a != b) {
                    din[b]++;
                    dout[a]++;
                } 
            }
        }

        int in = 0, out = 0;
        for (int i = 1; i <= scc_cnt; i++) {
            if (din[i] == 0)
                in++;
            if (dout[i] == 0)
                out++;
        }

        System.out.println(in);

        if (scc_cnt == 1)
            System.out.println(0);
        else
            System.out.println(Math.max(in, out));

    }
}
