/*
    最小点铺盖 = 最大匹配数
    A、B两台机器初始状态都为0，因此k个任务中，只要有可以被A、B任何一个状态0执行的可以直接跳过，不需要转换状态
    对于其余状态，我们从a向b连一条边，此时需要求的就是用最少的点将所有的边都覆盖，即最小点覆盖，那么我们直接求最大匹配数即可
*/

import java.io.*;
import java.util.Arrays;

public class J376 {
    static final int N = 110;
    static boolean[][] g = new boolean[N][N];
    static boolean[] st = new boolean[N];
    static int[] match = new int[N];
    static int n, m, k;

    static boolean find(int x) {
        for (int i = 1; i < m; i++) {
            if (!st[i] && g[x][i]) {
                st[i] = true;
                if (match[i] == 0 || find(match[i])) {
                    match[i] = x;
                    return true;
                }
            }
        }

        return false;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            Arrays.fill(st, false);
            Arrays.fill(match, 0);
            for (int i = 0; i < N; i++)
                Arrays.fill(g[i], false);

            String[] str = br.readLine().split(" ");
            n = Integer.parseInt(str[0]);
            if (n == 0)
                break;
            m = Integer.parseInt(str[1]);
            k = Integer.parseInt(str[2]);

            for (int i = 0; i < k; i++) {
                str = br.readLine().split(" ");
                int t = Integer.parseInt(str[0]);
                int a = Integer.parseInt(str[1]);
                int b = Integer.parseInt(str[2]);
                if (a == 0 || b == 0)
                    continue;
                g[a][b] = true;
            }

            int res = 0;
            for (int i = 1; i < n; i++) {
                Arrays.fill(st, false);
                if (find(i))
                    res++;
            }
            System.out.println(res);
        }
    }  
}
