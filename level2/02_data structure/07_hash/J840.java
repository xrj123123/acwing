import java.io.*;
import java.util.Arrays;

public class J840 {
    static final int N = 100003;
    static int[] h = new int[N], e = new int[N], ne = new int[N];
    static int idx;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Arrays.fill(h, -1);
        int n = Integer.parseInt(br.readLine());
        for (int i = 0; i < n; i++) {
            String[] str = br.readLine().split(" ");
            System.out.println(str[0] + " " + str[1]);
            if (str[0].equals("I")) {
                insert(Integer.parseInt(str[1]));
            } else if (str[0].equals("Q")) {
                if (query(Integer.parseInt(str[1])))
                    System.out.println("Yes");
                else
                    System.out.println("No");
            }
        }
        br.close();
    }

    public static void insert(int x) {
        int k = (x % N + N) % N;  // k表示在hash表的位置
        e[idx] = x;
        ne[idx] = h[k];
        h[k] = idx++;
    }

    public static boolean query(int x) {
        int k = (x % N + N) % N;
        for (int i = h[k]; i != -1; i = ne[i]){
            if (e[i] == x)
                return true;
        }
        return false;
    }
}