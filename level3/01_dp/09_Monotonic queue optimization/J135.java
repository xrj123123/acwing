import java.util.Scanner;

public class J135 {
    static final int N = 300010;
    static int[] s = new int[N], q = new int[N];
    static int n, m, hh, tt;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        m = sc.nextInt();

        for (int i = 1; i <= n; i++) {
            int x = sc.nextInt();
            s[i] = s[i - 1] + x;
        }

        int res = -0x3f3f3f3f;
        for (int i = 1; i <= n; i++) {
            if (q[hh] < i - m) hh++;
            res = Math.max(res, s[i] - s[q[hh]]);
            while (hh <= tt && s[q[tt]] >= s[i]) tt--;
            q[++tt] = i;
        }

        System.out.println(res);

        sc.close();
    }
}
