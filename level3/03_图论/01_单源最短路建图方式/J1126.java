import java.io.*;

public class J1126 {
    static final int N = 2010;
    static double[][] g = new double[N][N];
    static double[] dist = new double[N];
    static boolean[] st = new boolean[N];
    static int n, m, start, end;

    public static void Dijkstra(){
        dist[start] = 1;

        for (int i = 0; i < n; i++) {
            int t = -1;
            for (int j = 1; j <= n; j++){
                if (!st[j] && (t == -1 || dist[j] > dist[t]))
                    t = j;
            }
            st[t] = true;
            
            for (int j = 1; j <= n; j++)
                if (dist[t] * g[t][j] > dist[j])
                    dist[j] = dist[t] * g[t][j];
        }
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);

        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            int z = Integer.parseInt(str[2]);
            g[x][y] = g[y][x] = (100.0 - z) / 100; 
        }

        str = br.readLine().split(" ");
        start = Integer.parseInt(str[0]);
        end = Integer.parseInt(str[1]);

        Dijkstra();

        System.out.printf("%.8f", 100 / dist[end]);
    }
}
