/*
    题目求的是去掉的边的最大值，即求出最小生成树后，不在最小生成树中的边的权值之和
    但是题目中会存在最小生成森林，即多个最小生成树，所以需要使用Kruskal算法
*/

import java.io.*;
import java.util.*;

public class J1141 {
    static final int N = 210;
    static Node[] w = new Node[N];
    static int[] p = new int[N];
    static int n, k;

    static int find(int x){
        if (p[x] != x)
            p[x] = find(p[x]);
        return p[x];
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        k = Integer.parseInt(str[1]);

        for (int i = 1; i <= n; i++) p[i] = i;

        for (int i = 0; i < k; i++){
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            int c = Integer.parseInt(str[2]);
            w[i] = new Node(a, b, c);
        }

        Arrays.sort(w, 0, k, (a, b) -> a.c - b.c);

        int res = 0;
        for (int i = 0; i < k; i++){
            int a = find(w[i].a);
            int b = find(w[i].b);
            if (a != b)
                p[a] = b;
            else
                res += w[i].c;
        }
        System.out.println(res);
    }
}

class Node{
    int a;
    int b;
    int c;
    public Node(int a, int b, int c){
        this.a = a;
        this.b = b;
        this.c = c;
    }
}
