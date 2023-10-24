/*
    找到一个最小的d值，使得将所有权值大于d的边删除后，整个图形的连通块数量不超过k
    使用Kruskal算法，枚举每条边，如果当前两个点不在同一个连通块，那么将其合并，同时连通块数量减一，并记录当前两个连通块的距离
    当连通块数量小于等于k，那么退出，即剩下的点都可以放置卫星使其连接
*/

import java.io.*;
import java.util.*;

public class J1145{
    static final int N = 510, M = N * N / 2;
    static PII[] q = new PII[M];
    static Node[] edge = new Node[M];
    static int[] p = new int[N];
    static int n, k;

    static double get_dist(PII a, PII b){
        int x = a.x - b.x;
        int y = a.y - b.y;
        return Math.sqrt(x * x + y * y);
    }

    static int find(int x){
        if (x != p[x])
            p[x] = find(p[x]);
        return p[x];
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        k = Integer.parseInt(str[1]);

        for (int i = 0; i < n; i++) {
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            q[i] = new PII(x, y);
        }

        for (int i = 0; i < n; i++)
            p[i] = i;

        int idx = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++)
                edge[idx++] = new Node(i, j, get_dist(q[i], q[j]));
        
        Arrays.sort(edge, 0, idx, (a, b) -> Double.compare(a.w, b.w));

        int cnt = n;
        double res = 0;
        for (int i = 0; i < idx; i++) {
            if (cnt <= k)
                break;
            int a = find(edge[i].x);
            int b = find(edge[i].y);
            double w = edge[i].w;
            if (a != b){
                p[a] = b;
                cnt--;
                res = w;
            }
        }
        System.out.printf("%.2f", res);
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

class Node{
    int x;
    int y;
    double w;
    public Node(int x, int y, double w){
        this.x = x;
        this.y = y;
        this.w = w;
    }
}
