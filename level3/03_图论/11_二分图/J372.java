/*
    题目要求的是可以放1*2大小骨牌的数量，我们可以将1*2大小的骨牌想象成一条边，求的是边的数量的最大值，且边不能重叠，这就是最大匹配
    n*n的棋盘，可以分为奇数点和偶数点，我们可以发现任意两个相邻的点都是一个奇数点和一个偶数点，因此我们将棋盘通过奇数点和偶数点分为两个集合，即为二分图
    因此可以使用匈牙利算法求最大匹配
*/

import java.io.*;
import java.util.Arrays;

public class J372 {
    static final int N = 110;
    static boolean[][] g = new boolean[N][N], st = new boolean[N][N];
    static PII[][] match = new PII[N][N];
    static int n, m;

    static boolean find(int x, int y) {
        int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i], ty = y + dy[i];
            if (tx < 1 || tx > n || ty < 1 || ty > n)
                continue;
            if (g[tx][ty] || st[tx][ty])
                continue;
            st[tx][ty] = true;
            PII t = match[tx][ty];

            if (t == null || find(t.x, t.y)) {
                match[tx][ty] = new PII(x, y);
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);

        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            g[a][b] = true;
        }

        int res = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                if ((i + j) % 2 == 0 && !g[i][j]) {
                    for (int k = 0; k < N; k++)
                        Arrays.fill(st[k] , false);
                    if (find(i, j))
                        res++;
                }    
            }
        System.out.println(res);
    }
}

class PII {
    int x, y;
    public PII(int x, int y) {
        this.x = x;
        this.y = y;
    }
}
