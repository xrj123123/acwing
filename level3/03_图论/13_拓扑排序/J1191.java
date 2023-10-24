import java.io.*;
import java.util.*;

public class J1191 {
    static final int N = 110, M = 10010;
    static int[] h = new int[N], e = new int[M], ne = new int[M], cnt = new int[N];
    static int n, idx;

    static void add(int a, int b) {
        e[idx] = b;
        ne[idx] = h[a];
        h[a] = idx++;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(br.readLine());
        Arrays.fill(h, -1);
        for (int i = 1; i <= n; i++) {
            String[] str = br.readLine().split(" ");
            for (int j = 0; j < str.length - 1; j++) {
                int t = Integer.parseInt(str[j]);
                add(i, t);
                cnt[t]++;
            }
        }

        Queue<Integer> q = new LinkedList<>();
        for (int i = 1; i <= n; i++) {
            if (cnt[i] == 0)
                q.offer(i);
        }

        while (!q.isEmpty()) {
            int t = q.poll();
            System.out.print(t + " ");

            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                cnt[j]--;
                if (cnt[j] == 0) 
                    q.offer(j);
            }
        }
        System.out.println();
    }
}
