/*
 *  不能选连续K+1头奶牛，即每连续K+1头奶牛必须挑出来一头不选，求挑出来不选的最小值
 *  状态表示: f[i]表示挑出第i头牛不选，且方案合法的最小值
 *  状态计算: f[i] = w[i] + min(f[j]) (i-K-1 <= j <= i-1)  求f[j]的最小值，即维护一个窗口大小为K+1的滑动窗口
 */
import java.util.Scanner;

public class J1087_2 {
    static final int N = 100010;
    static long sum = 0;
    static long[] f = new long[N], w = new long[N], q = new long[N];
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(), K = sc.nextInt();
        for (int i = 1; i <= n; i++) {
            w[i] = sc.nextLong();
            sum += w[i];
        }
        
        int hh = 0, tt = 0;
        for (int i = 1; i <= n; i++) {
            if (q[hh] < i - K - 1) hh++;
            f[i] = f[(int)q[hh]] + w[i];
            while (hh <= tt && f[(int)q[tt]] >= f[i]) tt--;
            q[++tt] = (long)i;
        }
        long ans = (long)1e18 + 7;
        for (int i = n - K; i <= n; i++)
            ans = Math.min(ans, f[i]);
        
        System.out.println(sum - ans);
        sc.close();
    }
}
