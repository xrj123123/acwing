// acwing 173 矩阵距离
/*
    多源BFS
    求所有的0到1的最近距离，假设只有一个1，那么就可以把1当做起点，就是flood fill算法，1这个点依次向外扩展，即是所有0到1的最短距离
    但是现在有多个1，也就是有多个起点，那么在初始时，我们把所有的1都入队，然后做一遍bfs，每个0第一次被遍历到时就是最小距离
 */

import java.io.*;
import java.util.Arrays;

public class J173 {
    static final int N = 1010;
    static int[][] a = new int[N][N], dist = new int[N][N];
    static int[][] tr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    static P[] q = new P[N * N];
    static int n, m;
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
        for (int i = 0; i < n ; i++) {
            Arrays.fill(dist[i], -1);
            String s = br.readLine();
            for (int j = 0; j < m; j++)
                a[i][j] = s.charAt(j) - '0';
        }
   
        bfs();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m ; j++)
                bw.write(dist[i][j] + " ");
            bw.write("\n");
        }
        
        bw.close();
        br.close();
    }    
    
    public static void bfs() {
        int hh = 0, tt = -1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (a[i][j] == 1) {
                    dist[i][j] = 0;
                    q[++tt] = new P(i, j);
                }

        while (hh <= tt) {
            P t = q[hh++];

            for (int i = 0; i < 4; i++) {
                int tx = t.x + tr[i][0];
                int ty = t.y + tr[i][1];
                if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
                if (dist[tx][ty] != -1) continue;

                dist[tx][ty] = dist[t.x][t.y] + 1;
                q[++tt] = new P(tx, ty);
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