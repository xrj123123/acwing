import java.io.*;
import java.util.*;

public class J1116 {
    static final int N = 30;
    static boolean[][] st = new boolean[N][N];
    static int[] dx = {-1, -2, -2, -1, 1, 2, 2, 1}, dy = {-2, -1, 1, 2, 2, 1, -1, -2};
    static int n, m, x, y, res;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    
        int T = Integer.parseInt(br.readLine());
        while (T-- > 0) {
            String[] str = br.readLine().split(" ");
            n = Integer.parseInt(str[0]);
            m = Integer.parseInt(str[1]);
            x = Integer.parseInt(str[2]);
            y = Integer.parseInt(str[3]);

            for (int i = 0; i < n; i++)
                Arrays.fill(st[i], false);
            res = 0;
            st[x][y] = true;
            dfs(x, y, 1);
            System.out.println(res);
        }
    }

    public static void dfs(int x, int y, int tot) {
        if (tot == n * m) {
            res++;
            return;
        }

        for (int i = 0; i < 8; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
            if (st[tx][ty]) continue;
            st[tx][ty] = true;
            dfs(tx, ty, tot + 1);
            st[tx][ty] = false;
        }
    }
}
