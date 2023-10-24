import java.io.*;

public class J1144 {
    static final int N = 1010, M = 1000010, K = 2000010;
    static int[] p = new int[M];
    static Node[] nodes = new Node[K];
    static int[][] idx = new int[N][N];
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

        for (int i = 1, t = 0; i <= n; i++)
            for (int j = 1; j <= m; j++, t++)
                idx[i][j] = t;
        
        for (int i = 1; i <= n * m; i++)
            p[i] = i;

        int cnt = 0;
        
        // 纵向
        for (int j = 1; j <= m; j++)
            for (int i = 1; i < n; i++) {
                int a = idx[i][j];
                int b = idx[i + 1][j];
                nodes[cnt++] = new Node(a, b, 1);
            }
        
        // 横向
        for (int i = 1; i <= n; i++)    
            for (int j = 1; j < m; j++){
                int a = idx[i][j];
                int b = idx[i][j + 1];
                nodes[cnt++] = new Node(a, b, 2);
            }

        
        String data = "";
        while ((data = br.readLine()) != null) {
            str = data.split(" ");
            int x1 = Integer.parseInt(str[0]);
            int y1 = Integer.parseInt(str[1]);
            int x2 = Integer.parseInt(str[2]);
            int y2 = Integer.parseInt(str[3]);

            int a = find(idx[x1][y1]);
            int b = find(idx[x2][y2]);
            if (a != b){
                p[a] = b;
            }
        }

        int res = 0;
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
    public Node(int a, int b, int c){
        this.a = a;
        this.b = b;
        this.c = c;
    }
}
