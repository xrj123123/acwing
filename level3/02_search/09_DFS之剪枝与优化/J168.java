/*
    DFS + 剪枝
    1、优化搜索顺序
       从下往上枚举，同时，先枚举r，再枚举h【r是平方级别】，这样分支数量会小
    2、可行性剪枝
       因为每层r和h是单调递增，所以第u层最小为u
       u <= Ru <= min(R{u+1}-1, sqrt(n-v))
            n-v >= R^2*H, H最小取1, R <= sqrt(n-v)
       u <= Hu <= min(H{u+1}-1, (n-v)/R^2)
            n-v >= R^2*H, H <= (n-v)/R^2
       v+minv[u] <= n 当前已用体积加上前u层最小体积，如果大于n，就return
    3、最优性剪枝
       s+mins[u] < res  当前已用面积加上前u层最小面积如果大于当前res就return

       2*(n-v)/R[u+1] + s < res
 */

import java.io.*;

public class J168 {
    static final int N = 25, INF = 0x3f3f3f3f;
    static int[] H = new int[N], R = new int[N], minv = new int[N], mins = new int[N];
    static int n, m, res = INF;

    public static void dfs(int u, int v, int s) {
        if (v + minv[u] > n) return;
        if (s + mins[u] >= res) return;
        if (s + 2 * (n - v) / R[u + 1] >= res) return;

        if (u == 0) {
            if (v == n)
                res = s;
            return;
        }

        for (int r = Math.min(R[u + 1] - 1, (int)Math.sqrt(n - v)); r >= u; r--)
            for (int h = Math.min(H[u + 1] - 1, (n - v) / r / r); h >= u; h--) {
                R[u] = r;
                H[u] = h;
                int t = 0;
                if (u == m)
                    t = r * r;
                dfs(u - 1, v + r * r * h, s + 2 * r * h + t);
            }
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(br.readLine());
        m = Integer.parseInt(br.readLine());

        for (int i = 1; i <= m; i++) {
            minv[i] = minv[i - 1] + i * i * i;
            mins[i] = mins[i - 1] + 2 * i * i;
        }

        R[m + 1] = H[m + 1] = INF;
        
        dfs(m, 0, 0);
        if (res == INF)
            System.out.println(0);
        else
            System.out.println(res);
    }
}
