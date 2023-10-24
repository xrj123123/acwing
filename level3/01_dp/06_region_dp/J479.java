import java.util.*;;

public class J479 {
    static int N = 35;
    static int w[] = new int[N];
    static int f[][] = new int[N][N], g[][] = new int[N][N];

    static void dfs(int l, int r){
        if (l > r)  return;
        int root = g[l][r];
        System.out.print(root + " ");
        dfs(l, root - 1);
        dfs(root + 1, r);
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        for (int i = 1; i <= n; i++)
            w[i] = sc.nextInt();
        
        for (int len = 1; len <= n; len++)
            for (int l = 1; l + len - 1 <= n; l++){
                int r = l + len - 1;
                if (len == 1){
                    f[l][r] = w[l];
                    g[l][r] = l;
                    continue;
                }
                for (int k = l; k <= r; k++){
                    int left = k == l ? 1 : f[l][k - 1];
                    int right = k == r ? 1 : f[k + 1][r];
                    int score = left * right + w[k];
                    if (score > f[l][r])
                    {
                        f[l][r] = score;
                        g[l][r] = k;
                    }
                }
            }
        System.out.println(f[1][n]);
        dfs(1, n);
        sc.close();
    }
}
