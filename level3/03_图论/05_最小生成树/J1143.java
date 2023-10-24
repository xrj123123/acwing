import java.io.*;
import java.util.*;

public class J1143 {
    static final int N = 2010, M = 10010;
    static int[] p = new int[N];
    static Node[] nodes = new Node[M];
    static int n, m;

    static int find(int x){
        if (x != p[x])
            p[x] = find(p[x]);
        return p[x];
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);

        for (int i = 1; i <= n; i++)
            p[i] = i;
        
        int res = 0;
        int cnt = 0;
        for (int i = 0; i < m ; i++) {
            str = br.readLine().split(" ");
            int type = Integer.parseInt(str[0]);
            int a = Integer.parseInt(str[1]);
            int b = Integer.parseInt(str[2]);
            int c = Integer.parseInt(str[3]);
            if (type == 1){
                int pa = find(a);
                int pb = find(b);
                if (pa != pb)
                    p[pa] = pb;
                res += c;
            } else {
                nodes[cnt++] = new Node(a, b, c);
            }
        }

        Arrays.sort(nodes, 0, cnt, (a, b) -> a.c - b.c);

        for (int i = 0; i < cnt; i++) {
            int a = find(nodes[i].a);
            int b = find(nodes[i].b);
            if (a != b) {
                p[a] = b;
                res += nodes[i].c;
            }
        }
        System.out.println(res);
    }
}

class Node{
    int a;
    int b;
    int c;
    public Node(int a, int b, int c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }
}