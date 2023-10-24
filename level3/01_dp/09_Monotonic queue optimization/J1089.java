import java.util.Scanner;

/*  dp + 单调队列优化
 *  状态表示: f[i]表示当前在第i个烽火台，且点燃第i个烽火台的所有方案中的最小值
 *  状态计算: f[i] = min(f[j]) + w[i] (i-m <= j < i)
 *  求[i-m,i-1]之间的最小值，如果遍历时间复杂度就是n，但是可以发现这就是一个滑动窗口，可以通过单调队列来求最小值
 */
public class J1089 {
    static int N = (int)2e5 + 10;
    static int[] f = new int[N], w = new int[N], q = new int[N];
    static int n, m;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        m = sc.nextInt();
        
        for (int i = 1; i <= n; i++)
            w[i] = sc.nextInt();
        
        int hh = 0, tt = 0; // 初始队列里有个0，f[0]=0
        for (int i = 1; i <= n; i++) {
            if (q[hh] < i - m)
                hh++;
            f[i] = f[q[hh]] + w[i];
            while (hh <= tt && f[q[tt]] >= f[i])
                tt--;
            q[++tt] = i;
        }
        
        int res = 0x3f3f3f3f;
        for (int i = n - m + 1; i <= n; i++)
            res = Math.min(res, f[i]);
        
        System.out.println(res);

        sc.close();
    }
}
