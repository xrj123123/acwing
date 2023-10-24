/*
    求次小生成树
    方法一: 先求最小生成树，然后枚举树上的每一条边，去掉这条边，重新求最小生成树，最小值就是次小生成树，但是只能求出非严格次小生成树
    方法二: 先求最小生成树，然后枚举每条非树边，将该边加入树中，然后再从树上减去一条边，使得最终的图仍是一棵树，则一定可以求出次小生成树（严格或非严格）

    做法: 1.先求出最小生成树
          2.预处理出最小生成树中任意两点之间连边的最大值与次大值。求次小值是因为，如果非树边和当前两点之间的最大边权值相同，可以去替换次小值的边
          3.枚举每条非树边，将该非树边加到树上，假设该边的两个端点为a和b，此时会形成一个环，然后将a到b之间最大的边去掉即可，最终求最小值

*/

import java.io.*;
import java.util.*;

public class J1148 {
    static final int N = 510, M = 10010;
    static Node[] edge = new Node[M];
    static int[][] dist1 = new int[N][N], dist2 = new int[N][N];
    static int[] p = new int[N];
    static int[] h = new int[N], e = new int[2 * M], ne = new int[2 * M], w = new int[2 * M];
    static int n, m, idx;

    static void add(int a, int b, int c){
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static int find(int x) {
        if (p[x] != x)
            p[x] = find(p[x]);
        return p[x];
    }

    static void dfs(int u, int p, int maxd1, int maxd2, int[] d1, int[] d2){
        d1[u] = maxd1;
        d2[u] = maxd2;
        for (int i = h[u]; i != -1; i = ne[i]){
            int j = e[i];
            if (j != p) {
                int td1 = maxd1, td2 = maxd2;
                if (w[i] > td1) {
                    td2 = td1;
                    td1 = w[i];
                }else if (w[i] < td1 && w[i] > td2)
                    td2 = w[i];
                dfs(j, u, td1, td2, d1, d2);
            }
        }
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
        Arrays.fill(h, -1);

        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            int c = Integer.parseInt(str[2]);
            edge[i] = new Node(a, b, c);
        }

        for (int i = 0; i <= n; i++) 
            p[i] = i;

        Arrays.sort(edge, 0, m, (x, y) -> x.w - y.w);

        long sum = 0;
        long res = (long)1e18;
        for (int i = 0; i < m; i++) {
            int a = find(edge[i].x);
            int b = find(edge[i].y);
            int w = edge[i].w;
            if (a != b){
                p[a] = b;
                edge[i].f = true;
                sum += w;
                add(edge[i].x, edge[i].y, w);
                add(edge[i].y, edge[i].x, w);
            }
        }
        
        // 预处理任意两点之间的最大值与次大值, 初始化为最小值是为了避免次小值不存在的情况
        for (int i = 1; i <= n; i++) 
            dfs(i, -1, -(int)1e9, -(int)1e9, dist1[i], dist2[i]);
        
        // 枚举每一条非树边
        for (int i = 0; i < m; i++) {
            if (!edge[i].f) {
                long t = 0;
                int a = edge[i].x;
                int b = edge[i].y;
                int w = edge[i].w;
                if (w > dist1[a][b]) 
                    t = sum + w - dist1[a][b];
                else if (w > dist2[a][b])
                    t = sum + w - dist2[a][b];
                    
                res = Math.min(res, t);
            }
        }
        System.out.println(res);
    }   
}

class Node{
    int x;
    int y;
    int w;
    boolean f;
    public Node(int x, int y, int w){
        this.x = x;
        this.y = y;
        this.w = w;
    }
}
