/*
    题目要求是有n个点n-1条边，这样一棵树就是最小生成树，且是唯一的，此时需要将这棵树变为一个完全图，即任意两条边都连接
    我们在使用Kruskal算法时，每次连接最短的边，此时会将两个集合合并，在合并时，我们想要构成完全图就必须将左边集合和右边集合的所有边全部连起来
    因为最小生成树是唯一的，而且还要求增加的边的权值和最小，因此两个集合所有增加的边的权值应为w+1，w是当前连接两个集合的边的权值，即构成最小生成树
    所以在做Kruskal算法时，每连接一条边，那么将两个集合其他任意两条边的权值设为w+1并连接即可
*/

import java.io.*;
import java.util.*;

public class J346 {
    static final int N = 6010;
    static Node[] edges = new Node[N];
    static int[] p = new int[N], size = new int[N];
    static int n;

    static int find(int x) {
        if (x != p[x]){
            p[x] = find(p[x]);
        }
        return p[x];
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        for (int cases = 0; cases < t; cases++) {
            n = Integer.parseInt(br.readLine());
            for (int j = 0; j < n - 1; j++) {
                String[] str = br.readLine().split(" ");
                int a = Integer.parseInt(str[0]);
                int b = Integer.parseInt(str[1]);
                int c = Integer.parseInt(str[2]);
                edges[j] = new Node(a, b, c);
            }

            for (int i = 1; i <= n; i++){
                p[i] = i;
                size[i] = 1;
            }

            Arrays.sort(edges, 0, n - 1, (a, b) -> a.w - b.w);

            int res = 0;
            for (int i = 0; i < n - 1; i++) {
                int a = find(edges[i].x);
                int b = find(edges[i].y);
                int w = edges[i].w;
                if (a != b){
                    p[a] = b;
                    res += (size[a] * size[b] - 1) * (w + 1);
                    size[b] += size[a];
                }
            }
            System.out.println(res);
        }
    }
}

class Node{
    int x;
    int y;
    int w;
    public Node(int x, int y, int w){
        this.x = x;
        this.y = y;
        this.w = w;
    }
}
