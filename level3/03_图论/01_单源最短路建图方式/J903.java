/*
    根据题目实例，想要1号物品，有3种方式得到，得到2外加8000金币、得到3外加5000金币，或者直接花费10000金币，
    直接买的方式我们可以构建一个虚拟源点，这里把0号点作为虚拟源点，即从0号点到1号点的路径为10000,
    要得到2号物品，有两种方式，得到4号外加200金币，直接从0号点外加1000金币
    得到3号物品有两种方式，得到4号外加200金币，直接从0号点外加3000金币
    得到4号物品只有一种方式，即从0号点直接购买需要50金币
    这样就可以将图构建出来，题目求解的就是从虚拟源点即0号点到1号点的最短路径
    对于等级的限制，我们可以依次枚举每个等级区间，因为必须有1号点，因此从level[1]-m开始枚举,只有等级在[i, i+m]之间的可以进行购买，枚举所有区间求最小值   
 */

import java.io.*;
import java.util.Arrays;

public class J903 {
    static final int N = 110, INF = 0x3f3f3f3f;
    static int[] dist = new int[N], level = new int[N];
    static int[][] w = new int[N][N];
    static boolean[] st = new boolean[N];
    static int m, n;

    public static int Dijkstra(int low, int high){
        Arrays.fill(dist, INF);
        Arrays.fill(st, false);
        dist[0] = 0;

        for (int i = 1; i <= n + 1; i++){
            int t = -1;
            for (int j = 0; j <= n; j++){
                if (!st[j] && (t == -1 || dist[j] < dist[t]))
                    t = j;
            }
            st[t] = true;

            for (int j = 1; j <= n; j++){
                if (level[j] >= low && level[j] <= high)
                    dist[j] = Math.min(dist[j], dist[t] + w[t][j]);
            }
        }
        return dist[1];
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        m = Integer.parseInt(str[0]);
        n = Integer.parseInt(str[1]);

        for (int i = 1; i <= n; i++){
            Arrays.fill(w[i], INF);
            w[i][i] = 0;
        }

        for (int i = 1; i <= n; i++) {
            str = br.readLine().split(" ");
            int price = Integer.parseInt(str[0]);
            level[i] = Integer.parseInt(str[1]);
            int cnt = Integer.parseInt(str[2]);
            w[0][i] = price;
            for (int j = 0; j < cnt; j++) {
                str = br.readLine().split(" ");
                int id = Integer.parseInt(str[0]);
                int v = Integer.parseInt(str[1]);
                w[id][i] = v;
            }
        }

        // 枚举每个等级区间
        int res = INF;
        for (int i = level[1] - m; i <= level[1]; i++)
            res = Math.min(res, Dijkstra(i, i + m));

        System.out.println(res);
    }
}
