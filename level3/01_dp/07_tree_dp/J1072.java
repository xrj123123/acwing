import java.util.Scanner;
import java.lang.Math;
import java.util.Arrays;

public class J1072 {
    static int N = (int)1e5 + 10, M = 2 * N;
    static int[] h = new int[N], e = new int[M], ne = new int[M], w = new int[M];
    static int idx, res;

    public static void add(int a, int b, int c){
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }
    public static int dfs(int u, int father){
        int d1 = 0, d2 = 0;
        for (int i = h[u]; i != -1; i = ne[i]){
            int j = e[i];
            if (j == father) continue;
            int d = dfs(j, u) + w[i];
            if (d > d1){
                d2 = d1; 
                d1 = d;
            }   
            else if(d > d2)
                d2 = d;
        }
        res = Math.max(res, d1 + d2);
        return d1;
    }
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        Arrays.fill(h, -1);
        for (int i = 0; i < n - 1; i++){
            int a = sc.nextInt(), b = sc.nextInt(), c = sc.nextInt();
            add(a, b, c);
            add(b, a, c);
        }

        dfs(1, -1);
        System.out.println(res);
        sc.close();
    }
}
