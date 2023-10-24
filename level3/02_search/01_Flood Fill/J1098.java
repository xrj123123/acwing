// acwing 1098 城堡问题
/*
    Flood Fill问题，遍历每个点，如果当前点是房间，则将其向四周可扩充的地方扩充，然后标记已走
 */
import java.io.*;
public class J1098 {
    static final int N = 110;
    static int[][] g = new int[N][N];
    static boolean[][] st = new boolean[N][N];
    static P[] q = new P[N * N];
    static int[][] tr = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    static int n, m;
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String str[] = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
        for (int i = 0; i < n; i++) {
            str = br.readLine().split(" ");
            for (int j = 0; j < m; j++) {
                g[i][j] = Integer.parseInt(str[j]);
            }
        }
        int res = 0, area = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (!st[i][j]) {
                    res++;
                    area = Math.max(bfs(i, j), area);
                }
            }

        System.out.println(res);
        System.out.println(area);
        br.close();
    }

    public static int bfs(int x, int y) {
        int hh = 0, tt = 0;
        q[tt] = new P(x, y);
        st[x][y] = true;
        int sum = 1;

        while (hh <= tt) {
            P p = q[hh++];

            for (int i = 0; i < 4; i++) {
                int tx = p.x + tr[i][0];
                int ty = p.y + tr[i][1];
                if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
                if ((((g[p.x][p.y] >> i) & 1) == 1) || st[tx][ty]) continue;
                q[++tt] = new P(tx, ty);
                st[tx][ty] = true;
                sum++;
            }
        }
        return sum;
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
