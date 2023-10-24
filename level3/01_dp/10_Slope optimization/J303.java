// acwing 303 运输小猫
/*
    斜率优化
    首先分析，饲养员需要在小猫玩耍结束后才可以带走他，也就是说饲养员到达小猫位置的时间应该大于等于小猫玩耍结束的时间。即
    s+di >= ti, 其中s是饲养员出发时间，di是小猫所在山距离1号山的距离，ti是小猫玩耍结束时间，s >= ti-di，ti-di就是饲养员最早出发时间
    此时小猫等待时间就是 s+di-ti = s-(ti-di)，可以看到都和ti-di有关，令ai = ti-di，ai就是对于每只小猫来说，饲养员最早出发时间
    将每只小猫的ai从小到大排序，比如对于a3 a4 a5三只小猫，饲养员如果想把他们三个都接走，那么他最早出发时间是a5
    三只小猫等待时间为a5-a3 + a5-a4 + a5-a5 = 3*a5 - (a3+a4+a5) = 3*a5 - (sa5-sa2)，对于k时刻出发的饲养员，他可以带走的小猫满足ai<=k
    这就转换为了302任务安排2,某个饲养员在某个时间出发，可以带走连续的一段小猫，求小猫等待时间最小值
    状态表示: f[i][j]表示i个饲养员带走前j只小猫，小猫等待时间的最小值
    状态计算: f[i][j] = min(f[i-1][k] + a[j]*(j-k) - (sj-sk)) (0 <= k < j)
              f[i][j] = f[i-1][k] + a[j]*j - a[j]*k - sj + sk ==> f[i-1][k] + sk = a[j]*k + f[i][j] + sj - a[j]*j
              k和a[j]都是单调递增的，因此就转化为了凸包边界问题
 */

import java.util.*;

public class J303 {
    static final int N = 100010, P = 110;
    static long[] d = new long[N], t = new long[N], a = new long[N], s = new long[N];
    static int[] q = new int[N];
    static long[][] f = new long[P][N];
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        int p = sc.nextInt();
        for(int i = 2; i <= n; i++){
            d[i] = d[i-1] + sc.nextInt();
        }

        for(int i = 1; i <= m; i++){
            int h = sc.nextInt();
            t[i] = sc.nextInt();
            a[i] = t[i] - d[h];
        }

        Arrays.sort(a, 1, m + 1);        
        for(int i = 1; i <= m; i++) 
            s[i] = s[i - 1] + a[i]; 
        
        for (int i = 0; i <= p; i++) {
            Arrays.fill(f[i], Long.MAX_VALUE);
            f[i][0] = 0;
        }

        for (int i = 1; i <= p; i++) {
            int hh = 0, tt = 0;
            q[tt] = 0;  // 初始队列中存了f[i][0],即带走0只小猫
            for (int j = 1; j <= m; j++) {
                // 把队头小于当前斜率的删除
                while (hh < tt && (get_y(i, q[hh + 1]) - get_y(i, q[hh])) <= (q[hh + 1] - q[hh]) * a[j]) hh++;

                // 计算当前f[i][j]
                f[i][j] = f[i - 1][q[hh]] + a[j] * j - a[j] * q[hh] - s[j] + s[q[hh]];

                // 当前点加入后，删除队尾不在凸包上的点
                while (hh < tt && (get_y(i, q[tt]) - get_y(i, q[tt - 1])) * (j - q[tt]) >= (q[tt] - q[tt - 1]) * (get_y(i, j) - get_y(i, q[tt])))
                    tt--;
                q[++tt] = j;
            }
        }
        System.out.println(f[p][m]);
        sc.close();
    }

    public static long get_y(int i, int k) {
        return f[i - 1][k] + s[k];
    }
}
