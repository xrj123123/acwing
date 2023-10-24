/*
    我们需要求的是让所有矿井通电所需的最小费用，每个矿井可以和其他通电的矿井相连或者自身建一个发电站，此时我们可以建立一个虚拟源点，对于每个矿井，
    将其自身建一个发电站的费用作为它到虚拟源点之间的费用，假设虚拟源点是一个超级发电站，这样就变成了一个n+1个点的最小生成树问题
*/
import java.io.*;
import java.util.Arrays;

public class J1146 {
    static final int N = 310;
    static int[][] w = new int[N][N];
    static int[] dist = new int[N];
    static boolean[] st = new boolean[N];
    static int n;

    static int Prim(){
        int res = 0;
        Arrays.fill(dist, 0x3f3f3f3f);
        dist[0] = 0;
        for (int i = 0; i < n + 1; i++) {
            int t = -1;
            for (int j = 0; j < n + 1; j++) {
                if (!st[j] && (t == -1 || dist[t] > dist[j]))
                    t = j;
            }

            st[t] = true;
            res += dist[t];

            for (int j = 0; j < n + 1; j++)
                dist[j] = Math.min(dist[j], w[t][j]);
        }
        return res;
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(br.readLine());
        for (int i = 1; i <= n; i++){
            int v = Integer.parseInt(br.readLine());
            w[0][i] = w[i][0] = v;
        }

        for (int i = 1; i <= n; i++) {
            String[] str = br.readLine().split(" ");
            for (int j = 1; j <= n; j++)
                w[i][j] = w[j][i] = Integer.parseInt(str[j - 1]);
        }

        System.out.println(Prim());
    }
}
