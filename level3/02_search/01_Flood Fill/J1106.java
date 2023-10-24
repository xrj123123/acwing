// acwing 1106 山峰和山谷
import java.io.*;

public class J1106 {
    static final int N = 1010, M = N * N;
    static int[][] g = new int[N][N];
    static boolean[][] st = new boolean[N][N];
    static P[] q = new P[M];
    static boolean ishigher, islower;
    static int n;
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(br.readLine());
        for (int i = 0; i < n; i++) {
            String[] str = br.readLine().split(" ");
            for (int j = 0; j < n; j++) 
                g[i][j] = Integer.parseInt(str[j]);
        }

        int peak = 0, valley = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (!st[i][j]) {
                    ishigher = false;
                    islower = false;
                    bfs(i, j);
                    if (!ishigher) peak++;
                    if (!islower) valley++;
                }
            }

        System.out.println(peak + " " + valley);

        br.close();
    }

    public static void bfs(int x, int y) {
        int hh = 0, tt = 0;
        q[tt] = new P(x, y);
        st[x][y] = true;

        while (hh <= tt) {
            P p = q[hh++];

            for (int i = p.x - 1; i <= p.x + 1; i++)
                for (int j = p.y - 1; j <= p.y + 1; j++) {
                    if (i == p.x && j == p.y) continue;
                    if (i < 0 || i >= n || j < 0 || j >= n) continue;
                    
                    if (g[i][j] != g[p.x][p.y]) {
                        if (g[i][j] > g[p.x][p.y]) ishigher = true;
                        else islower = true;
                    } else if(!st[i][j]) {
                        st[i][j] = true;
                        q[++tt] = new P(i, j);
                    }
                }
        }
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