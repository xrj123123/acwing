import java.util.Scanner;

public class J1085 {
    final static int N = 10;
    static int[][] f = new int[N][10];

    static void init() {
        for (int i = 0; i <= 9; i++)
            if (i != 4)
                f[1][i] = 1;
        for (int i = 2; i < 10; i++)
            for (int j = 0; j <= 9; j++) {
                if (j == 4) continue;
                for (int k = 0; k <= 9; k++) {
                    if (k == 4 || j == 6 && k == 2) continue;
                    f[i][j] += f[i - 1][k];
                }
            }
    }

    static int dp(int n) {
        if (n == 0) return 1;
        int res = 0;
        int last = 0;   // 上一位数字
        int[] nums = new int[10];
        int t = 0;
        while (n > 0) {
            nums[t++] = n % 10;
            n /= 10;
        }

        for (int i = t - 1; i >= 0; i--) {
            int x = nums[i];
            for (int j = 0; j < x; j++) {
                if (j == 4 || last == 6 && j == 2) continue;
                res += f[i + 1][j];
            }

            if (x == 4 || last == 6 && x == 2) break;
            last = x;
            if (i == 0) res++;
        }

        return res;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        init();
        while (true) {
            int l = sc.nextInt(), r = sc.nextInt();
            if (l == 0 && r == 0) break;
            System.out.println(dp(r) - dp(l - 1));
        }        
        sc.close();
    }
    
}
