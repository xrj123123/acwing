import java.util.Scanner;

public class J1083 {
    static int N = 11;
    static int[][] f = new int[N][N];

    static void init(){
        for (int i = 0; i <= 9; i++) f[1][i] = 1;
        for (int i = 2; i < N; i++)
            for (int j = 0; j <= 9; j++)
                for (int k = 0; k <= 9; k++)
                    if (Math.abs(j - k) >= 2)
                        f[i][j] += f[i - 1][k];
    }

    static int dp(int n){
        if (n == 0) return 0;
        int res = 0;
        int last = -2;
        int[] nums = new int[N];
        int t = 0;
        while (n != 0){
            nums[t++] = n % 10;
            n /= 10;
        }

        for (int i = t - 1; i >= 0; i--){
            int x = nums[i];
            for (int j = 0; j < x; j++){
                if (i == t - 1 && j == 0) continue;
                if (Math.abs(last - j) >= 2)
                    res += f[i + 1][j];
            }
            if (Math.abs(x - last) < 2) break;
            last = x;
            if (i == 0) res++;
        }

        for (int i = 1; i < t; i++)
            for (int j = 1; j <= 9; j++)
                res += f[i][j];
        return res;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int l = sc.nextInt(), r = sc.nextInt();

        init();

        System.out.println(dp(r) - dp(l - 1));

        sc.close();
    }
}
