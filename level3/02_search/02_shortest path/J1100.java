// acwing 1100 抓住那头牛
import java.io.*;

public class J1100 {
    static final int N = 100010;
    static boolean[] st = new boolean[N];
    static int[] dist = new int[N], q = new int[N];
    static int n, k;
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        k = Integer.parseInt(str[1]);

        System.out.println(bfs(n));

        br.close();
    }

    public static int bfs(int sx) {
        int hh = 0, tt = 0;
        q[tt] = sx;
        st[sx] = true;
        dist[sx] = 0;
        
        while (hh <= tt) {
            int x = q[hh++];

            int tx = x - 1;
            if (tx >= 0 && tx <= 100000 && !st[tx]) {
                q[++tt] = tx;
                st[tx] = true;
                dist[tx] = dist[x] + 1;
            }

            tx = x + 1;
            if (tx >= 0 && tx <= 100000 && !st[tx]) {
                q[++tt] = tx;
                st[tx] = true;
                dist[tx] = dist[x] + 1;
            }

            tx = x * 2;
            if (tx >= 0 && tx <= 100000 && !st[tx]) {
                q[++tt] = tx;
                st[tx] = true;
                dist[tx] = dist[x] + 1;
            }
        }

        return dist[k];
    }

}
