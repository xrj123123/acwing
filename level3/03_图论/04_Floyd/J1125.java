/*
    牧区表示每个点, 通过路径相连。首先建图, 两点之间有边, 我们计算其距离, 没有边就赋值为INF, 通过邻接矩阵可得
    然后跑一遍floyd, 在将每个点离他最远的距离存在dmax中, 然后求dmax最大值就是所有牧场的直径最大值res1
    枚举所有值为INF的边, 将该边连上, 长度为dmax[i] + dmax[j] + get(i, j), 求出所有连边的最小值res2
    最后结果就是res1和res2的最大值
*/

import java.io.*;

public class J1125 {
    static final int N = 160;
    static final double INF = 1e10;
    static double[][] d = new double[N][N];
    static double[] dmax = new double[N];
    static PII[] q = new PII[N];
    static char[][] g = new char[N][N];
    static int n;

    static double get(PII a, PII b){
        int dx = a.x - b.x;
        int dy = a.y - b.y;
        return Math.sqrt(dx * dx + dy * dy);
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(br.readLine());
        for (int i = 0; i < n; i++){
            String[] str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            q[i] = new PII(x, y);
        }
        for (int i = 0; i < n; i++) {
            g[i] = br.readLine().toCharArray();
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (g[i][j] == '1')
                    d[i][j] = get(q[i], q[j]);
                else if (i == j)
                    d[i][j] = 0;
                else
                    d[i][j] = INF;
            }
        
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    d[i][j] = Math.min(d[i][j], d[i][k] + d[k][j]);
        
        // 求每个点的最远距离
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][j] < INF)
                    dmax[i] = Math.max(dmax[i], d[i][j]);
        
        double res1 = 0;
        for (int i = 0; i < n; i++)
            res1 = Math.max(res1, dmax[i]);

        // 枚举所有未连接的点, 将其连接, 然后求最短直径
        double res2 = INF;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][j] == INF) {
                    res2 = Math.min(res2, dmax[i] + dmax[j] + get(q[i], q[j]));
                }
        
        double res = Math.max(res1, res2);
        System.out.printf("%f", res);
    }
}

class PII{
    int x;
    int y;
    public PII(int x, int y){
        this.x = x;
        this.y = y;
    }
}
