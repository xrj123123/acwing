/*
    xi <= xi+1
    xb - xa <= l  ==> xb <= xa + l
    xb - xa >= d  ==> xa <= xb - d
*/

import java.io.*;
import java.util.*;

public class J1170 {
    static final int N = 1010, M = 20010;
    static int[] dist = new int[N], cnt = new int[N];
    static boolean[] st = new boolean[N];
    static int[] h = new int[N], e = new int[M], ne = new int[M], w = new int[M];
    static int n, ml, md, idx;

    static void add(int a, int b, int c) {
        e[idx] = b;
        ne[idx] = h[a];
        w[idx] = c;
        h[a] = idx++;
    }

    static boolean spfa(int x) {
        Arrays.fill(st, false);
        Arrays.fill(cnt, 0);
        Queue<Integer> q = new LinkedList<>();
        Arrays.fill(dist, 0x3f3f3f3f);
        q.offer(x);
        dist[x] = 0;
        st[x] = true;
    
        while (!q.isEmpty()) {
            int t = q.poll();
            st[t] = false;
            
            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (dist[j] > dist[t] + w[i]) {
                    dist[j] = dist[t] + w[i];
                    cnt[j] = cnt[t] + 1;
                    if (cnt[j] >= n)
                        return false;
                    if (!st[j]) {
                        st[j] = true;
                        q.offer(j);
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
        ml = Integer.parseInt(str[1]);
        md = Integer.parseInt(str[2]);
        Arrays.fill(h, -1);

        for (int i = 1; i < n; i++)
            add(i + 1, i, 0);

        while (ml-- > 0) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            int c = Integer.parseInt(str[2]);
            if (a > b)
                add(b, a, c);
            else
                add(a, b, c);
        }

        while (md-- > 0) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            int c = Integer.parseInt(str[2]);
            if (a > b)
                add(a, b, -c);
            else
                add(b, a, -c);
        }


        if (!spfa(n)) {
            System.out.println(-1);
        } else {
            spfa(1);
            if (dist[n] == 0x3f3f3f3f) {
                System.out.println(-2);
            } else {
                System.out.println(dist[n]);
            }
        }
    }
}
