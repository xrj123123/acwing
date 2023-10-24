/*
    题目求的是最少糖果，因此求的是最小值，也就是求最长路
    对于X=1，A=B => A >= B, B >= A
    X=2, A<B => B >= A + 1
    X=3, A>=B => A >= B
    X=4, A>B => A >= B + 1
    X=5, A<=B => B >= A
    同时每个小朋友都要分到糖果，因此Xi >= 1, 找到虚拟源点0，建一条0->Xi, 边长为1的边
    因为虚拟源点0可以到达每一个点，所以就会到达每一条边
*/
import java.io.*;
import java.util.*;

public class J1169 {
    static final int N = 100010, M = 300010;
    static int[] h = new int[N], e = new int[M], ne = new int[M], w = new int[M];
    static long[] dist = new long[N]; 
    static int[] cnt = new int[N];
    static boolean[] st = new boolean[N];
    static int n, k, idx;

    static void add(int a, int b, int c) {
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static boolean spfa(){
        Arrays.fill(dist, -0x3f3f3f3f);
        Stack<Integer> q = new Stack<Integer>();
        dist[0] = 0;
        q.push(0);

        while (!q.isEmpty()) {
            int t = q.pop();
            st[t] = false;

            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (dist[j] < dist[t] + w[i]) {
                    dist[j] = dist[t] + w[i];
                    cnt[j] = cnt[t] + 1;
                    if (cnt[j] >= n + 1) {
                        return false;
                    }
                    if (!st[j]) {
                        st[j] = true;
                        q.push(j);
                    }
                }
            }
        }
        return true;
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        k = Integer.parseInt(str[1]);

        Arrays.fill(h, -1);
        for (int i = 1; i <= n; i++) {
            add(0, i, 1);
        }
        
        while (k-- > 0) {
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int a = Integer.parseInt(str[1]);
            int b = Integer.parseInt(str[2]);
            if (x == 1) {
                add(a, b, 0);
                add(b, a, 0);
            } else if (x == 2) {
                add(a, b, 1);
            } else if (x == 3) {
                add(b, a, 0);
            } else if (x == 4) {
                add(b, a, 1);
            } else {
                add(a, b, 0);
            }
        }

        if (!spfa()) {
            System.out.println(-1);
        } else {
            long res = 0;
            for (int i = 1; i <= n; i++)
                res += dist[i];
            System.out.println(res);
        }
    }
}
