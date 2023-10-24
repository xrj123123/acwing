/*
    差分约束 + 前缀和
    由满足ai ≤ x ≤bi的整数x不少于ci个，我们可以想到前缀和，S(bi) - S(ai-1) >= ci
    因为ai, bi的取值为[0,50000], 所以我们将每个ai, bi都加1，这样取值范围为[1,50001]
    令Si表示1到i之间取了多少个数，最终求的是S[50001]的最小值，即1-50001最少选多少个数
    Si >= Si-1 
    Si - Si-1 <= 1 ==> Si-1 >= Si - 1   即每个数选的个数小于等于1 
    Sb - S(a-1) >= c ==> Sb >= S(a-1) + c
*/

import java.io.*;
import java.util.*;

public class J362 {
    static final int N = 50010;
    static int[] dist = new int[N];
    static boolean[] st = new boolean[N];
    static int[] h = new int[N], e = new int[3 * N], ne = new int[3 * N], w = new int[3 * N];
    static int n, idx;

    static void add(int a, int b, int c) {
        e[idx] = b;
        ne[idx] = h[a];
        w[idx] = c;
        h[a] = idx++;
    }

    static void spfa() {
        Arrays.fill(dist, -0x3f3f3f3f);
        Queue<Integer> q = new LinkedList<>();
        dist[0] = 0;
        st[0] = true;
        q.offer(0);

        while (!q.isEmpty()) {
            int t = q.poll();
            st[t] = false;

            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (dist[j] < dist[t] + w[i]) {
                    dist[j] = dist[t] + w[i];
                    if (!st[j]) {
                        q.offer(j);
                        st[j] = true;
                    }
                }
            }
        }
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(br.readLine());
        Arrays.fill(h, -1);

        for (int i = 1; i <= 50001; i++) {
            add(i - 1, i, 0);
            add(i, i - 1, -1);
        }

        for (int i = 0; i < n; i++) {
            String[] str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            int c = Integer.parseInt(str[2]);
            a++;
            b++;
            add(a - 1, b, c);
        }

        spfa();

        System.out.println(dist[50001]);
    }
}
