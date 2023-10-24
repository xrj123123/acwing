/*
    题目要求出图中一个至少包含3个点的环，且环的长度最小
    我们可以从集合的角度出发，以每个环中点的最大编号划分，可以划分为1, 2 ... n-1, n，共n中方案，对于每一种方案，求出环的最小值
    因为floyd算法，本质上是一个dp，第一重循环k表示从i到j只经过了1-k之间的边的最小值
    所以在第k重循环开始时，此时已经求出的是任意i到j只经过1到k-1之间的边的最小值，所以此时以k作为最大编号，
    d[i][j]的最小值已经在前k-1次循环求出，枚举i和j，求出d[i][j]+w[i][k]+w[k][j]的最小值
    对于输出方案，因为在floyd中，d[i][j] > d[i][k] + d[k][j], 所以d[i][j] = d[i][k] + d[k][j], i到j一定是经过k的
    令pos[i][j] = k表示从i到j的最短路是通过点k求出的，然后递归求出i到k之间的点和k到j之间的点
*/
import java.io.*;
import java.util.*;

public class J344 {
    static final int N = 110;
    static int[][] d = new int[N][N], g = new int[N][N], pos = new int[N][N];
    static int[] path = new int[N];
    static int n, m, cnt;

    static void get_path(int i, int j){
        if (pos[i][j] == 0)
            return;
        int k = pos[i][j];
        get_path(i, k);
        path[cnt++] = k;
        get_path(k, j);
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
        
        for (int i = 0; i < N; i++)
            Arrays.fill(g[i], 0x3f3f3f3f);
        
        for (int i = 1; i <= m; i++) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            int c = Integer.parseInt(str[2]);
            g[a][b] = g[b][a] = Math.min(g[a][b], c);
        }

        for (int i = 0; i < N; i++)
            d[i] = Arrays.copyOf(g[i], g[i].length);
       
        long res = 0x3f3f3f3f;
        for (int k = 1; k <= n; k++){
            for (int i = 1; i < k; i++)
                for (int j = i + 1; j < k; j++){
                    if ((long)d[i][j] + g[i][k] + g[k][j] < res){
                        res = d[i][j] + g[i][k] + g[k][j];
                        cnt = 0;
                        path[cnt++] = k;
                        path[cnt++] = i;
                        get_path(i, j);
                        path[cnt++] = j;
                    }
                }

            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++){
                    if (d[i][j] > d[i][k] + d[k][j]){
                        d[i][j] = d[i][k] + d[k][j];
                        pos[i][j] = k;
                    }
                }
        }

        if (res == 0x3f3f3f3f)
            System.out.println("No solution.");
        else{
            for (int i = 0; i < cnt; i++)
                System.out.print(path[i] + " ");
            System.out.println();
        }

    }    
}
