// acwing 188 武士风度的牛
import java.io.*;

public class J188 {
    static final int N = 155;
    static char[][] g = new char[N][N];
    static boolean[][] st = new boolean[N][N];
    static int[][] dist = new int[N][N];
    static int[][] tr = {{-2, -1}, {-1, -2}, {-2, 1}, {-1, 2}, {1, -2}, {2, -1}, {1, 2}, {2, 1}};
    static P[] q = new P[N * N];
    static int n, m, sx, sy, ex, ey;
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String str[] = br.readLine().split(" ");
        m = Integer.parseInt(str[0]);
        n = Integer.parseInt(str[1]);
        for (int i = 0; i < n; i++) {
            String line = br.readLine();
            for (int j = 0; j < m; j++) {
                g[i][j] = line.charAt(j);
                if (g[i][j] == 'K') {
                    sx = i; sy = j;
                }
                if (g[i][j] == 'H') {
                    ex = i; ey = j;
                }
            }
        }

        System.out.println(bfs(sx, sy));

        br.close();
    }

    public static int bfs(int sx, int sy) {
        int hh = 0, tt = 0;
        q[tt] = new P(sx, sy);
        st[sx][sy] = true;
        dist[sx][sy] = 0;

        while (hh <= tt) {
            P t = q[hh++];
            
            for (int i = 0; i < 8; i++) {
                int tx = t.x + tr[i][0];
                int ty = t.y + tr[i][1];
                if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
                if (g[tx][ty] == '*' || st[tx][ty]) continue;

                q[++tt] = new P(tx, ty);
                st[tx][ty] = true;
                dist[tx][ty] = dist[t.x][t.y] + 1;
            }

        }

        return dist[ex][ey];
    }
}

class P{
    int x;
    int y;
    public P(int x, int y) {
        this.x = x;
        this.y = y;
    }
}
