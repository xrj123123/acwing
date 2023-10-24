/*
    最小生成树
    可以用Prim算法做的题一定可以使用Kruskal来做，但是可以使用Kruskal做的不一定可以使用Prim做
    一般稠密图用邻接矩阵存储，使用Prim算法
    Prim算法：每次将不在当前最小生成树中且距离当前最小生成树最近的点，加入到最小生成树中 O(n^2)
    证明：假设本次不选最近的点的这条边，最终也得到了一棵树。然后将这条边加上，会形成一个环，
        在这个环上，一定可以找出一条长度不小于当前边的边，那么把当前边替换上去，结果一定不会变差
    Kruskal算法: 将所有的边从小到大排序，枚举每条边a、b, 其权重为c, 如果点a和点b不连通, 那么将这条边加入集合, 即两个集合合并 O(mlogm)
    证明同Prim算法
*/

import java.io.*;
import java.util.Arrays;

public class J1140 {
    static final int N = 110;
    static int[][] w = new int[N][N];
    static int[] dist = new int[N];  // dist[i]表示如果i不在集合中, 距离集合最短距离
    static boolean[] st = new boolean[N];
    static int n;

    static int Prim(){
        int res = 0;
        Arrays.fill(dist, 0x3f3f3f3f);
        dist[1] = 0;

        for (int i = 0; i < n; i++) {
            int t = -1;
            for (int j = 1; j <= n; j++){
                if (!st[j] && (t == -1 || dist[t] > dist[j]))
                    t = j;
            }
            st[t] = true;
            res += dist[t];

            // 用点t更新其他不在最小生成树中的点的距离
            for (int j = 1; j <= n; j++) {
                dist[j] = Math.min(dist[j], w[t][j]);
            }
        }
        return res;
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);

        for (int i = 0; i < N; i++)
            Arrays.fill(w[i], 0x3f3f3f3f);

        for (int i = 1; i <= n; i++){
            str = br.readLine().split(" ");
            for (int j = 1; j <= n; j++)
                w[i][j] = Integer.parseInt(str[j - 1]);
        }

        System.out.println(Prim());
    }    
}
