/*  acwing 302 任务安排3
 *  和任务安排2不同点在于，这道题Ti可以小于0，可以看一下上一道题的式子
 *  f[i] = f[j] - (sumt[i] + s) * sumc[j] + sumt[i] * sumc[i] + s * sumc[n] 
 *  f[j] = (sumt[i] + s) * sumc[j] + f[i] -  sumt[i] * sumc[i] - s * sumc[n]
 *  sumt[i] + s 就不是单调递增的了，因此在查询时，不能将队头小于当前斜率的点都删除，因为队头比当前斜率小的点可能会被后边的斜率大
 *  查询时，使用二分来找到第一个比当前斜率大的点
 *  插入时，因此Ci还是大于0，所以sumc[i]一定是单调递增的，所以插入时将队尾不在凸包上的点删除
 *  时间复杂度为nlogn
 */
import java.util.Scanner;

public class J302 {
    static int N = (int)3e5 + 10;
    static long[] f = new long[N], t = new long[N], c = new long[N];
    static int [] q = new int[N];
    static int n, s;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        s = sc.nextInt();
        for (int i = 1; i <= n; i++) {
            t[i] = sc.nextInt();
            c[i] = sc.nextInt();
            t[i] += t[i - 1];
            c[i] += c[i - 1];
        }

        int hh = 0, tt = 0;
        q[0] = 0;
        for (int i = 1; i <= n; i++) {
            // 二分查找大于等于当前斜率的最小的点
            int l = hh, r = tt;
            while (l < r) {
                int mid = l + r >> 1;
                // mid+1不会超出tt的范围，如果mid==tt，那么l = r = tt，是进不来循环的
                if (f[q[mid + 1]] - f[q[mid]] >= (t[i] + s) * (c[q[mid + 1]] - c[q[mid]])) 
                    r = mid;
                else
                    l = mid + 1;
            }

            f[i] = f[q[r]] - (t[i] + s) * c[q[r]] + t[i] * c[i] + s * c[n];

            // 删除队尾不在凸包上的点
            while (hh < tt && (double)(f[i] - f[q[tt - 1]]) * (c[q[tt]] - c[q[tt - 1]]) <= (double)(c[i] - c[q[tt - 1]]) * (f[q[tt]] - f[q[tt - 1]]))
                tt--;
            q[++tt] = i;
        }

        System.out.println(f[n]);

        sc.close();
    }   
}
