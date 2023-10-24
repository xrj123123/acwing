/*  acwing 301 任务安排2
 *  斜率优化
 *  f[i] = min(f[j] + sumt[i] * (sumc[i] - sumc[j]) + s * (sumc[n] - sumc[j]))  (0 <= j < i)
 *  普通dp时间复杂度为n^2，这里会超时，因此需要用到斜率优化
 *  上边式子中，j是变量，因此可以转化为 
 *  f[i] = f[j] - (sumt[i] + s) * sumc[j] + sumt[i] * sumc[i] + s * sumc[n] 
 *  f[j] = (sumt[i] + s) * sumc[j] + f[i] -  sumt[i] * sumc[i] - s * sumc[n] 
 *  将f[j]看做y，sumc[j]看做x，sumt[i]+s看做斜率k，该方程就是y=k*x+b
 *  因此可以看做当前平面上有很多点(x0, y0)...(xi-1, yi-1)，用一个斜率为sumt[i]+s的直线去拟合这些点，找到截距的最小值
 *  因此该直线遇到的第一个点就是截距最小值点，即找到第一个斜率大于sumt[i]+s的点，这些点的外围会形成一个凸包
 *  因为斜率sumt[i] + s是单调递增的，而且x为sumc[j]也是单调递增的
 *      在查询的时候，可以将队头小于当前斜率的点全部删除
 *      在插入的时候，将队尾所有不在凸包上的点全部删除
 *  [0, i-1]区域上只有凸包上的点才可以取，因此将这些点放到队列中
 *  在枚举f[i]时，找到第一个比他大的斜率的点，队头斜率比他小的点就可以删除
 *  在队尾插入当前点时，必须形成凸包，因此插入的这个点和上上一个点的斜率如果小于上个点和上上个点的斜率，那么就删除上一个点
 */
import java.util.Scanner;

public class J301 {
    static final int N = (int)3e5 + 10;
    static long[] f = new long[N], t = new long[N], c = new long[N];
    static int[]q = new int[N];
    static int n, s;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        s = sc.nextInt();
        for (int i = 1; i <= n; i++) {
            t[i] = sc.nextLong();
            c[i] = sc.nextLong();
            t[i] += t[i - 1];
            c[i] += c[i - 1];
        }

        int hh = 0, tt = 0; // 初始队列中中有f[0]，即选前0个任务
        q[0] = 0;
        for (int i = 1; i <= n; i++) {
            // 删除队头元素,需要保证队列至少两个元素
            while (hh < tt && (f[q[hh + 1]] - f[q[hh]]) <= (c[q[hh + 1]] - c[q[hh]]) * (t[i] + s)) 
                hh++;
            f[i] = f[q[hh]] - (t[i] + s) * c[q[hh]] + t[i] * c[i] + s * c[n];

            // 插入队尾，删除队尾不是凸包边界的元素
            while (hh < tt && (f[q[tt]] - f[q[tt - 1]]) * (c[i] - c[q[tt - 1]]) >= (f[i] - f[q[tt - 1]]) * (c[q[tt]] - c[q[tt - 1]])) {
                tt--;
            } 
            q[++tt] = i;
        }

        System.out.println(f[n]);

        sc.close();
    }
}
