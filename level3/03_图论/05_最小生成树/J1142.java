import java.io.*;
import java.util.*;

public class J1142 {
    static final int N = 310, M = 8010;
    static int[] p = new int[N];
    static Node[] nodes = new Node[M];
    static int n, m;

    static int find(int x){
        if (p[x] != x)
            p[x] = find(p[x]);
        return p[x];
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);

        for (int i = 0; i < m; i++){
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            int c = Integer.parseInt(str[2]);
            nodes[i] = new Node(a, b, c);
        }

        for (int i = 1; i <= n; i++)
            p[i] = i;

        Arrays.sort(nodes, 0, m, (a, b) -> a.c - b.c);
        
        int maxv = 0;
        for (int i = 0; i < m; i++) {
            int a = find(nodes[i].a);
            int b = find(nodes[i].b);
            if (a != b) {
                p[a] = b;
                maxv = Math.max(maxv, nodes[i].c);
            }
        }
        System.out.println(n - 1 + " " + maxv);
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
