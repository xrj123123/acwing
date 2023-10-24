// acwing 1076 迷宫问题
import java.io.*;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
public class J1076 {
    static final int N = 1010;
    static int[][] g = new int[N][N], dist = new int[N][N];
    static boolean[][] st = new boolean[N][N];
    static P[] q = new P[N * N];
    static P[][] pre = new P[N][N];
    static int[][] tr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    static int n;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(br.readLine());
        for (int i = 0; i < n; i++) {
            String str[] = br.readLine().split(" ");
            for (int j = 0; j < n ; j++)
                g[i][j] = Integer.parseInt(str[j]);
        }
            
        bfs();

        br.close();
    }

    public static void bfs() {
        int hh = 0, tt = 0;
        q[tt] = new P(0, 0);
        st[0][0] = true;
        dist[0][0] = 0;
        
        while (hh <= tt) {
            P t = q[hh++];

            for (int i = 0; i < 4; i++) {
                int tx = t.x + tr[i][0];
                int ty = t.y + tr[i][1];
                if (tx < 0 || tx >= n || ty < 0 || ty >= n) continue;
                if (g[tx][ty] == 1 || st[tx][ty]) continue;
                dist[tx][ty] = dist[t.x][t.y] + 1;
                st[tx][ty] = true;
                P tmp = new P(tx, ty);
                q[++tt] = tmp;
                pre[tx][ty] = t;
                if (tx == n - 1 && ty == n - 1) {
                    P now = tmp;
                    List<P> list = new ArrayList<>();
                    while (now.x != 0 || now.y != 0) {
                        list.add(now);
                        now = pre[now.x][now.y];
                    }
                    list.add(new P(0, 0));
                    Collections.reverse(list);
                    for (int k = 0; k < list.size(); k++) {
                        System.out.println(list.get(k).x + " " + list.get(k).y);
                    }
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
