import java.io.*;
import java.util.*;
/*
public class J1113 {
    static final int N = 25;
    static char[][] g = new char[N][N];
    static boolean[][] st = new boolean[N][N];
    static int n, m, x, y;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            String[] str = br.readLine().split(" ");
            m = Integer.parseInt(str[0]);
            n = Integer.parseInt(str[1]);
            if (m == 0 && n == 0) break;
            for (int i = 0; i < n; i++) {
                Arrays.fill(st[i], false);
                String s = br.readLine();
                for (int j = 0; j < m; j++) {
                    g[i][j] = s.charAt(j);
                    if (s.charAt(j) == '@') {
                        x = i; 
                        y = j;
                    }
                }     
            }

            System.out.println(bfs());
        }
    }

    public static int bfs() {
        int res = 1;
        LinkedList<PII> q = new LinkedList<>();
        int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
        q.offer(new PII(x, y));
        st[x][y] = true;

        while (!q.isEmpty()) {
            PII t = q.poll();

            for (int i = 0; i < 4; i++) {
                int tx = t.x + dx[i];
                int ty = t.y + dy[i];
                if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
                if (st[tx][ty]) continue;
                if (g[tx][ty] == '#') continue;
                q.offer(new PII(tx, ty));
                st[tx][ty] = true;
                res++;
            }
        }
        return res;
    }
}

class PII{
    int x;
    int y;
    public PII(int x, int y) {
        this.x = x; 
        this.y = y;
    }
}
*/

public class J1113{
    static final int N = 25;
    static char[][] g = new char[N][N];
    static boolean[][] st = new boolean[N][N];
    static int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
    static int n, m, x, y;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            String[] str = br.readLine().split(" ");
            m = Integer.parseInt(str[0]);
            n = Integer.parseInt(str[1]);
            if (m == 0 && n == 0) break;
            for (int i = 0; i < n; i++) {
                Arrays.fill(st[i], false);
                String s = br.readLine();
                for (int j = 0; j < m; j++) {
                    g[i][j] = s.charAt(j);
                    if (s.charAt(j) == '@') {
                        x = i; 
                        y = j;
                    }
                }     
            }

            System.out.println(dfs(x ,y));
        }
    }
    public static int dfs(int x, int y) {
        int cnt = 1;
        st[x][y] = true;

        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
            if (st[tx][ty]) continue;
            if (g[tx][ty] == '#') continue;
            cnt += dfs(tx, ty);
        }
        return cnt;
    }
}