/*
    bfs + dp + 二进制
    假如迷宫中没有门, 那么这道题就是一道普通的bfs求最短路问题了, 但是加上了门和钥匙, 我们就不能仅仅用(x,y)坐标来表示当前点的状态了
    为了表示当前的钥匙状态, 我们应该加一维状态来表示钥匙, 用一个二进制数来表示钥匙的状态, 二进制某一位为1表示有该类钥匙
    d[x][y][state]表示从起点(1,1)到(x,y)位置, 当前钥匙状态为state时的最短路径, 我们可以将二维坐标转为一维
    d[x][state]表示从第一个点到第x个点且钥匙状态为state时的最短路
    状态计算: 如果当前点有钥匙, 那么我们直接拿上，然后去下一个点【y总的方法是,拿起钥匙不移动【此时代价为0】,因此使用双端bfs, 而拿起钥匙直接去下一个点, 用bfs即可】
    如果下一个点是墙或者是门但是没钥匙, 那么就不能走; 如果下一个点是空地或者是门且有钥匙, 那么我们就走过去
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class J1131 {
    static final int N = 11, M = N * N;
    // g[i][j]表示第i个点和第j个点之间的状态, 0表示墙, -1表示通路, 大于0表示门
    // idx[i][j]表示第i行第j列的点对应的编号
    // d[i][j]表示从1号点走到i号点, 当前钥匙状态为j时的最短路
    // key[i]表示第i个点的钥匙
    static int[][] g = new int[M][M], idx = new int[N][N], d = new int[M][1 << N];
    static int[] key = new int[M];
    static boolean[][] st = new boolean[M][1 << N];
    static int n, m, p, k, s;

    public static int bfs(){
        for (int i = 0; i < M; i++)
            Arrays.fill(d[i], 0x3f3f3f3f);
        d[1][key[1]] = 0;
        Queue<PII> q = new LinkedList<>();
        q.offer(new PII(1, key[1]));
        st[1][key[1]] = true;
        int[] dx = {-1, 0, 1, 0};
        int[] dy = {0, 1, 0, -1};

        while (!q.isEmpty()){
            PII t = q.poll();
            st[t.x][t.state] = false;
            
            //System.out.println(t.x + " " + t.state);
            if (t.x == m * n)
                return d[t.x][t.state];
            int x = (t.x - 1) / m + 1;
            int y = (t.x - 1) % m + 1;
            int state = t.state;

            for (int i = 0; i < 4; i++){
                int tx = x + dx[i];
                int ty = y + dy[i];
                if (tx <= 0 || tx > n || ty <= 0 || ty > m)
                    continue;
                int next = idx[tx][ty];
                int nkey = state | key[next];
                
                
                if (st[next][nkey])
                    continue;
                if (g[t.x][next] == 0) // 墙
                    continue;
                if (g[t.x][next] > 0 && (t.state & (1 << g[t.x][next])) == 0) // 门且没有钥匙
                    continue;
                
                // 有钥匙或者空地
                if (d[next][nkey] > d[t.x][state] + 1){
                    d[next][nkey] = d[t.x][state] + 1;
                    q.offer(new PII(next, nkey));
                    st[next][nkey] = true;
                }     
            }
        }
        return -1;
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
        p = Integer.parseInt(str[2]);

        // idx[i][j]表示(i,j)对应的编号
        for (int i = 1, t = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                idx[i][j] = t++;
        for (int i = 0; i < M; i++)
            Arrays.fill(g[i], -1);

        k = Integer.parseInt(br.readLine());
        while (k-- > 0) {
            str = br.readLine().split(" ");
            int x1 = Integer.parseInt(str[0]);
            int y1 = Integer.parseInt(str[1]);
            int x2 = Integer.parseInt(str[2]);
            int y2 = Integer.parseInt(str[3]);
            int c = Integer.parseInt(str[4]);
            int d1 = idx[x1][y1];
            int d2 = idx[x2][y2];
            g[d1][d2] = g[d2][d1] = c;  // 0为墙, 大于0为门, -1表示通路
        }

        s = Integer.parseInt(br.readLine());
        while (s-- > 0){
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            int z = Integer.parseInt(str[2]);
            key[idx[x][y]] |= (1 << z);
        }

        System.out.println(bfs());
    }
}

class PII{
    int x;
    int state;
    public PII(int x, int state){
        this.x = x;
        this.state = state;
    }
}
