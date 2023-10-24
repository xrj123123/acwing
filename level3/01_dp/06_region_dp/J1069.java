import java.math.BigInteger;
import java.util.*;

/*
    java高精度方法
    返回值为BigInteger类型：add()，subtract()，multiply()，divide()，min(). max();
 */
public class J1069 {
    static int N = 55;
    static BigInteger w[] = new BigInteger[N];
    static BigInteger f[][] = new BigInteger[N][N];
    static String INF = "1000000000000000000000000000000";  // 高精度的正无穷1e30
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in); 
        int n = sc.nextInt();
        for (int i = 1; i <= n; i++)
            w[i] = sc.nextBigInteger();
        
        // BigInteger初始为null，要初始化为0
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                f[i][j] = new BigInteger("0");
        
        for (int len = 3; len <= n; len++){
            for (int l = 1; l + len - 1 <= n; l++){
                int r = l + len - 1;
                f[l][r] = new BigInteger(INF);
                for (int k = l + 1; k < r; k++){
                    BigInteger t = w[l].multiply(w[k]).multiply(w[r]);
                    t = t.add(f[l][k]).add(f[k][r]);
                    f[l][r] = f[l][r].min(t);
                }
            }
        }   
        System.out.println(f[1][n]);
        sc.close();
    }
}
