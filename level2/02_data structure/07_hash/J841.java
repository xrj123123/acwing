import java.io.*;

public class J841 {
    static final int P = 131, N = 100010;
    static long[] p = new long[N], h = new long[N];    // p[i]表示P^i, h[i]表示前i个字母的hahs值
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        int n = Integer.parseInt(str[0]);
        int m = Integer.parseInt(str[1]);
        String s = br.readLine();
        s = " " + s;
        
        p[0] = 1;
        for (int i = 1; i <= n; i++) {
            p[i] = p[i - 1] * P;
            h[i] = h[i - 1] * P + s.charAt(i);
        }

        for (int i = 0; i < m ; i++) {
            str = br.readLine().split(" ");
            int l1 = Integer.parseInt(str[0]), r1 = Integer.parseInt(str[1]), l2 = Integer.parseInt(str[2]), r2 = Integer.parseInt(str[3]);
            if (get(l1, r1) == get(l2, r2))
                System.out.println("Yes");
            else
                System.out.println("No");
        }
        br.close();
    }

    public static long get(int l, int r) {
        return h[r] - h[l - 1] * p[r - l + 1];
    }
}
