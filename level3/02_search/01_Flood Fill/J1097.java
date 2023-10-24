// acwing 1097 池塘计数
/*
    Flood Fill模型，可以对每个格子进行遍历，如果当前格子有雨水，那么就向四周蔓延，将有雨水的都标记一下，这就是一个区域
    遍历时，每找到一个新的有雨水的格子，res++
 */
import java.io.*;
public class J1097 {
    static final int N = 1010, M = N * N;
    static char[][] g = new char[N][N];
    static boolean[][] st = new boolean[N][N];
    static int n, m, res;
    static P[] q = new P[M];
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        String line = br.readLine();
        String str[] = line.split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);

        for (int i = 0; i < n; i++) {
            line = br.readLine();
            for (int j = 0; j < m; j++)
                g[i][j] = line.charAt(j);
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 'W' && !st[i][j]) {
                    res++;
                    bfs(i , j);
                }
            }
        bw.write(res + "");
        bw.close();
        br.close();
    }

    public static void bfs(int x, int y) {
        int hh = 0, tt = 0;
        q[tt] = new P(x, y);
        st[x][y] = true;

        while (hh <= tt) {
            P p = q[hh];
            hh++;

            for (int i = p.x - 1; i <= p.x + 1; i++)
                for (int j = p.y - 1; j <= p.y + 1; j++) {
                    if (i == p.x && j == p.y) continue;
                    if (i < 0 || i >= n || j < 0 || j >= m) continue;
                    if (g[i][j] == '.' || st[i][j]) continue;
                    q[++tt] = new P(i, j);
                    st[i][j] = true;
                }
        }
    }
        
}

class P{
    int x;
    int y;
    public P(int x, int y){
        this.x = x;
        this.y = y;
    }
}
