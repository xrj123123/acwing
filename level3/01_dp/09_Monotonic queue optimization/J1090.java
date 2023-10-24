/*
    二分 + dp + 单调队列
    求最长空题数的最小值（最大值最小），二分空题数量，假设为limit
    如果最长空题数量为limit，求最小消耗时间，和1089烽火传递这道题是一样的，如果最小消耗时间小于t，说明limit可以继续减小，向左二分，否则增大，向右二分
 */
import java.util.Scanner;

public class J1090 {
    static int N = (int)5e4 + 10;
    static int[] w = new int[N], f = new int[N], q = new int[N];
    static int n, t;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        t = sc.nextInt();
        for (int i = 1; i <= n; i++)
            w[i] = sc.nextInt();
        
        int l = 0, r = n; 
        while (l < r) {
            int mid = l + r >> 1;
            if (check(mid)) {
                r = mid;
            }else
                l = mid + 1;
        }
        System.out.println(r);

        sc.close();
    }

    public static boolean check(int limit) {
        int hh = 0, tt = 0;
        for (int i = 1; i <= n; i++) {
            if (q[hh] < i - limit - 1) hh++;
            f[i] = f[q[hh]] + w[i];
            while (hh <= tt && f[q[tt]] >= f[i]) 
                tt--;
            q[++tt] = i;
        }

        for (int i = n - limit + 1; i <= n; i++)
            if (f[i] <= t)
                return true;
        return false;
    }
}
