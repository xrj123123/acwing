// acwing 300 任务安排1
/*
 *  状态表示: f[i]表示执行前i个任务，费用的最小值
 *  状态计算: 求f[i]的最小值，就要划分上一批任务执行到哪一个，上一批任务可以执行到0,1,2...i-1
 *            用sumt表示时间的前缀和，sumc表示费用的前缀和。
 *            启动时间s可以额外计算，当某一批启动时，他就会有一个s，此时s会对之后所有的任务都有一个额外花费
 *            f[i] = min(f[j] + sumt[i] * (sumc[i] - sumc[j]) + s * (sumc[n] - sumc[j]))  (0 <= j < i)
 */

import java.util.Arrays;
import java.util.Scanner;

class J300 {
    final static int N = 5010;
    static long[] f = new long[N];
    static int[] sumt = new int[N], sumc = new int[N];
    static int n, s;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        s = sc.nextInt();
        for (int i = 1; i <= n; i++) {
            int t = sc.nextInt();
            int c = sc.nextInt();
            sumt[i] = sumt[i - 1] + t;
            sumc[i] = sumc[i - 1] + c;
        }

        Arrays.fill(f, Long.MAX_VALUE);
        f[0] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++)
                f[i] = Math.min(f[i], f[j] + (long)sumt[i] * (sumc[i] - sumc[j]) + s * (sumc[n] - sumc[j]));

        System.out.println(f[n]);
        
        sc.close();
    }
}

