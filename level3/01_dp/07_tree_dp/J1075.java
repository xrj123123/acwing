import java.util.Scanner;
import java.util.Arrays;

public class J1075 {
    static int N = 50010;
    static int[] h = new int[N], e = new int[N], ne = new int[N];
    static int[] sum = new int[N];
    static boolean[] st = new boolean[N];
    static int n, res, idx;

    public static void add(int a, int b){
        e[idx] = b;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    public static int dfs(int u){
        int d1 = 0, d2 = 0;
        for (int i = h[u]; i != -1; i = ne[i]){
            int j = e[i];
            int d = dfs(j) + 1;
            if (d > d1){
                d2 = d1;
                d1 = d;
            }else if (d > d2){
                d2 = d;
            }
        }
        res = Math.max(res, d1 + d2);
        return d1;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        Arrays.fill(h, -1);
        for (int i = 1; i <= n; i++)
            for (int j = 2; j <= n / i; j++)
                sum[i * j] += i;
        
        for (int i = 2; i <= n; i++){
            if (sum[i] < i){
                add(sum[i], i);
                st[i] = true;
            }
        }

        for (int i = 1; i <= n; i++)
            if (st[i] == false)
                dfs(i);

        System.out.println(res);

        sc.close();
    }
}
