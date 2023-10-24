/*
    floyd求闭包传递
    如果a -> b, b -> c, 推出a -> c, 就是闭包传递
    对于floyd算法, 如果a -> b, 那么d[a][b] = 1, 否则d[a][b] = 0
    图构建出来后, 跑一遍floyd, 如果d[a][k] = 1, d[k][b] = 1, 那么d[a][b] = 1

    对于题目中的3种关系, m个等式, 如果前k个确定了关系, 那么退出并输出次序
    如果出现矛盾, 即d[a][a] = 1, 那么退出
    m个等式循环结束后, 没有出现以上两种情况, 则不能确定
*/

import java.io.*;
import java.util.*;

public class J343 {
    static final int N = 26;
    static boolean[][] g = new boolean[N][N], d = new boolean[N][N];
    static boolean[] st = new boolean[N];
    static int n, m;

    static void floyd(){
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    d[i][j] |= (d[i][k] && d[k][j]);
    }

    static int check(){
        for (int i = 0; i < n; i++)
            if (d[i][i]) return 2;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (!d[i][j] && !d[j][i])
                    return 0;
        return 1;
    }

    static char get_min(){
        for (int i = 0; i < n; i++){
            if (st[i]) continue;
            boolean flag = true;
            for (int j = 0; j < n; j++) {
                if (!st[j] && d[j][i]){
                    flag = false;
                    break;
                }
            }
            if (flag){
                st[i] = true;
                return (char)(i + 'A');
            }
        }
        return ' ';
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str;
        while ((str = br.readLine().split(" ")) != null){
            for (int i = 0; i < N; i++)
                Arrays.fill(d[i], false);
            Arrays.fill(st, false);
                
            n = Integer.parseInt(str[0]);
            m = Integer.parseInt(str[1]);
            if (n == 0 && m == 0)
                break;
            
            // type为0表示未确定, 1表示有解, 2表示矛盾
            int type = 0, t = 0;
            for (int i = 1; i <= m; i++){
                char[] s = br.readLine().toCharArray();
                int a = s[0] - 'A';
                int b = s[2] - 'A';

                if (type == 0) {
                    d[a][b] = true;
                    floyd();
                    type = check();
                    if (type != 0) 
                        t = i;
                }
            }

            if (type == 0)
                System.out.println("Sorted sequence cannot be determined.");
            else if (type == 2)
                System.out.printf("Inconsistency found after %d relations.\n", t);
            else{
                System.out.printf("Sorted sequence determined after %d relations: ", t);
                for (int i = 0; i < n; i++)
                    System.out.print(get_min());
                System.out.println(".");
            }
                
        }
    }
}
