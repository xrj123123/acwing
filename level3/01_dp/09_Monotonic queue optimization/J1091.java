/*  acwing 1091 理想的正方形
 *  单调队列
 *  一般的单调队列是求一维的区间最小最大值，这道题相当于二维单调队列，求一个n*n的矩阵的最大最小值
 *  可以将二维单调队列转为一维来做
 *  首先对于每一行做单调队列，每个区间的最小值或最大值存在该区间最后一个元素的位置上
 *  每行求完之后，在对每一列做一个单调队列
 *  假设当前求最小值，矩阵大小n*n，那么现在这个n*n的矩阵的每一行的最小值都在最后一列存着
 *  对最后一列做一个单调队列，最小值存放在最下方位置，那么这个位置的值就是整个矩阵的最小值。求最大值同理
 */
import java.util.Scanner;;

public class J1091 {
    static final int N = 1010;
    static int[][] w = new int[N][N], num_min = new int[N][N], num_max = new int[N][N];
    static int[] q = new int[N];
    static int n, m, k;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        m = sc.nextInt();
        k = sc.nextInt();
        
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                w[i][j] = sc.nextInt();
        
        for (int i = 1; i <= n; i++) {
            get_min(w[i], num_min[i], m);   // 每行做一个单调队列求区间最小值
            get_max(w[i], num_max[i], m);   // 每行做一个单调队列求区间最大值
        }

        int res = (int)1e9;
        // 对列做单调队列
        int[] a = new int[N], b = new int[N], c = new int[N];
        for (int j = k; j <= m; j++) {
            for (int i = 1; i <= n; i++) a[i] = num_min[i][j];
            get_min(a, b, n);

            for (int i = 1; i <= n; i++) a[i] = num_max[i][j];
            get_max(a, c, n);

            for (int i = k; i <= n; i++)
                res = Math.min(res, c[i] - b[i]);
        }
        System.out.println(res);
        sc.close();
    }

    public static void get_min(int a[], int b[], int tot) {
        int hh = 0, tt = -1;
        for (int i = 1; i <= tot; i++) {
            if (q[hh] <= i - k) hh++;
            while (hh <= tt && a[q[tt]] >= a[i]) tt--;
            q[++tt] = i;
            b[i] = a[q[hh]];
        }
    }

    public static void get_max(int a[], int b[], int tot) {
        int hh = 0, tt = -1;
        for (int i = 1; i <= tot; i++) {
            if (q[hh] <= i - k) hh++;
            while (hh <= tt && a[q[tt]] <= a[i]) tt--;
            q[++tt] = i;
            b[i] = a[q[hh]];
        }
    }
}
