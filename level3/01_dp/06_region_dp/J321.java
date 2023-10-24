import java.util.*;
public class J321 {
    static int N = 15, M = 9;
    static int n, m = 8;
    static double X;
    static double INF = 1e9;
    static double f[][][][][] = new double[M][M][M][M][N];
    static int s[][] = new int[M][M];

    static double get(int x1, int y1, int x2, int y2){
        double sum = s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1] - X;
        return (double)(sum * sum / n);
    }

    static double dp(int x1, int y1, int x2, int y2, int k){
        double v = f[x1][y1][x2][y2][k];
        if (v >= 0)
            return v;
        if (k == 1)
            return f[x1][y1][x2][y2][k] = get(x1, y1, x2, y2);
        
        v = INF;
        for (int i = x1; i < x2; i++){
            v = Math.min(v, get(x1, y1, i, y2) + dp(i + 1, y1, x2, y2, k - 1));
            v = Math.min(v, get(i + 1, y1, x2, y2) + dp(x1, y1, i, y2, k - 1));
        }

        for (int i = y1; i < y2; i++){
            v = Math.min(v, get(x1, y1, x2, i) + dp(x1, i + 1, x2, y2, k - 1));
            v = Math.min(v, get(x1, i + 1, x2, y2) + dp(x1, y1, x2, i, k - 1));
        }
        return f[x1][y1][x2][y2][k] = v;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
                for (int k = 0; k < M; k++)
                    for (int s = 0; s < M; s++)
                        Arrays.fill(f[i][j][k][s], -1);

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++){
                s[i][j] = sc.nextInt();
                s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
            }
        X = (double)s[m][m] / n;
        
        System.out.printf("%.3f", (Math.sqrt(dp(1, 1, m, m, n))));

        sc.close();        
    }
}
