/*
    01分数规划
    对于这类求一个分数最大值问题，我们可以通过二分将其转换为求负环、最小生成树等问题
*/

import java.io.*;
import java.util.*;

public class J361 {
    static final int N = 1010, M = 5010;
    static int[] wf = new int[N];
    static int[] h = new int[N], e = new int[M], ne = new int[M], wt = new int[M], cnt = new int[N];
    static double[] dist = new double[N];
    static boolean[] st = new boolean[N];
    static int idx, n, m;
    
    static void add(int a, int b, int c) {
        e[idx] = b;
        wt[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static boolean check(double mid) {
        Arrays.fill(cnt, 0);
        Queue<Integer> q = new LinkedList<>();
        for (int i = 1; i <= n; i++) {
            q.offer(i);
            st[i] = true;
        }

        while (!q.isEmpty()) {
            int t = q.poll();
            st[t] = false;

            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (dist[j] < dist[t] + wf[t] - mid * wt[i]) {
                    dist[j] = dist[t] + wf[t] - mid * wt[i];
                    cnt[j] = cnt[t] + 1;
                    if (cnt[j] >= n)
                        return true;
                    if (!st[j]) {
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
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
        Arrays.fill(h, -1);

        for (int i = 1; i <= n; i++)
            wf[i] = Integer.parseInt(br.readLine());
        
        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            int c = Integer.parseInt(str[2]);
            add(a, b, c);
        }

        double l = 0, r = 1000;
        while (r - l > 1e-4) {
            double mid = (l + r) / 2;
            if (check(mid))
                l = mid;
            else
                r = mid;
        }
        System.out.printf("%.2f", r);
    }
}
