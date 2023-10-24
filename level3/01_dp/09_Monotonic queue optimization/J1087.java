/*  dp + 单调队列优化
 *  状态表示: f[i]表示从前i头牛中选，且合法的最大值 
 *  状态计算: 如果不选第i头牛，就是f[i-1]。
 *            如果选第i头牛，假设连续选了j头牛一直到i（i-j+1, i-j+2, ..., i）此时不能选i-j这头牛
 *            f[i] = s[i] - s[i-j] + f[i-j-1] = f[i-j-1] - s[i-j] + s[i] (1 <= j <= K)。求f[i-j-1] - s[i-j]的最大值
 *            令g(x) = f[x-1] - s[x]  (i-K <= x <= i-1)  相当于维护一个大小为K的滑动窗口，求窗口最大值问题
 *              g(0) = f(-1) - s[0]， g(0)表示j=i，相当于把i前边所有的牛都选了，是有意义的
 *              g(0) = f(0) - s[0] = 0
 *          所以，f[i] = max(f[i-1], g(j) + s[i]) (i-K <= j <= i-1)
 */
import java.util.Scanner;

public class J1087 {
    static final int N = 100010;
    static long[] s = new long[N], f = new long[N], q = new long[N];

    public static long g(int i) {
        if (i == 0) return 0;
        return f[i - 1] - s[i];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(), K = sc.nextInt();
        for (int i = 1; i <= n; i++) {
            s[i] = sc.nextLong();
            s[i] += s[i - 1];
        }

        int hh = 0, tt = 0; // 初始存放了g(0)表示全选
        for (int i = 1; i <= n; i++) {
            if (q[hh] < i - K) hh++;
            f[i] = Math.max(f[i - 1], g((int)q[hh]) + s[i]);
            while (hh <= tt && g((int)q[tt]) <= g(i)) tt--;
            q[++tt] = i;
        }
        
        System.out.println(f[n]);

        sc.close();
    }
}
