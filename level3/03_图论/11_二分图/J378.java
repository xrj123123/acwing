/*
    题目要求在棋盘上放尽可能多的骑士，并且他们之间不能相互攻击到。
    如果两个骑士可以相互攻击到，那么我们将他们连一条边，此时我们求的就是找出最多的点，使其任意两个点之间没有连边，即最大独立集=n-最小点覆盖=n-最大匹配数
    而在棋盘上，我们通过奇数点和偶数点将棋盘分为两个集合，可以发现任意边的两个顶点一定在不同的集合
    假设一个点(x,y)，他连边的另一个点一定是±1、±2的，这样最终是±一个奇数，所以奇偶性会改变，因此是二分图
*/

import java.io.*;
import java.util.Arrays;

public class J378 {
    static final int N = 110;
    static boolean[][] g = new boolean[N][N], st = new boolean[N][N];
    static PII[][] match = new PII[N][N];
    static int[] dx = {-1, -2, -2, -1, 1, 2, 2, 1}, dy = {-2, -1, 1, 2, 2, 1, -1, -2};
    static int n, m, t;

    static boolean find(int x, int y) {
        for (int i = 0; i < 8; i++) {
            int tx = x + dx[i], ty = y + dy[i];
            if (tx < 1 || tx > n || ty < 1 || ty > m)
                continue;
            if (g[tx][ty] || st[tx][ty])
                continue;
            st[tx][ty] = true;
            PII a = match[tx][ty];
            if (a == null || find(a.x, a.y)) {
                match[tx][ty] = new PII(x, y);
                return true;
            }
        }
        return false;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
        t = Integer.parseInt(str[2]);

        for (int i = 0; i < t; i++) {
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            g[x][y] = true;
        }

        int res = 0;
        for (int i = 1; i <= n; i++) 
            for (int j = 1; j <= m; j++) {
                for (int k = 0; k < N; k++)
                    Arrays.fill(st[k], false);
                if ((i + j) % 2 == 0 || g[i][j])
                    continue;
                if (find(i, j))
                    res++;
            }

        System.out.println(n * m - t - res);
    }
}

class PII {
    int x, y;
    public PII(int x, int y) {
        this.x = x;
        this.y = y;
    }
}
