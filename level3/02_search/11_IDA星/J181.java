/*
    IDA*
    我们可以依次枚举每种操作方案，因为要字典序最小，所以按ABCDEFGH的顺序进行DFS，当搜到第k层时，如果k+f(k) > depth，直接退出
    因为目标状态是中间8个位置值相等，所以估价函数f可以定义为8-cnt，cnt是中间8个位置出现次数最多的数字的次数，因为每次操作只会改变1个数字
    所以至少需要8-cnt次操作才可以达到目标状态
    剪枝: 当上一次进行了A操作，那么这次就不可以进行F操作，即不能进行逆操作
 */

 import java.io.*;
 /*
  *        0     1 
  *        2     3
  * 4  5   6  7  8  9 10 
  *       11    12
  * 13 14 15 16 17 18 19 
  *       20    21
  *       22    23
  */
 
 public class J181 {
     static final int N = 24;
     static int[] q = new int[N];
     static int[][] op = {
         {0, 2, 6, 11, 15, 20, 22},
         {1, 3, 8, 12, 17, 21, 23},
         {10, 9, 8, 7, 6, 5, 4},
         {19, 18, 17, 16 ,15, 14, 13},
         {23, 21 ,17, 12 ,8, 3, 1},
         {22, 20, 15, 11, 6, 2, 0},
         {13, 14, 15, 16, 17, 18, 19},
         {4, 5, 6, 7, 8, 9, 10},
     };
     static int[] path = new int[100];
     static int[] center = {6, 7, 8, 12, 17, 16, 15, 11};
     static int[] oppose = {5, 4, 7, 6, 1, 0, 3, 2};
 
     public static int f(){
         int[] sum = new int[4];
         for (int i = 0; i < 8; i++) sum[q[center[i]]]++;
 
         int cnt = 0;
         for (int i = 1; i <= 3; i++)
             cnt = Math.max(cnt, sum[i]);
         return 8 - cnt;
     }
 
     public static void operate(int i){
         int t = q[op[i][0]];
         for (int k = 0; k < 6; k++) 
             q[op[i][k]] = q[op[i][k + 1]];
         q[op[i][6]] = t;
     }
 
     public static boolean dfs(int u, int depth, int last) {
         if (u + f() > depth) return false;
         if (f() == 0) return true;
 
         for (int i = 0; i < 8; i++) {
             if (oppose[i] == last) continue;
             operate(i);
             path[u] = i;
             if (dfs(u + 1, depth, i)) return true;
             operate(oppose[i]);
         }
 
         return false;
     }
 
     public static void main(String[] args) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
         while (true) {
             String[] str = br.readLine().split(" ");
             if ("0".equals(str[0]))
                 break;
             for (int i = 0; i < N; i++) 
                 q[i] = Integer.parseInt(str[i]);
             
             int depth = 0;
             while (!dfs(0, depth, -1)) depth++;
 
             if (depth == 0) 
                 System.out.print("No moves needed");
             else
                 for (int i = 0; i < depth; i++)
                     System.out.print((char)(path[i] + 'A'));
             System.out.println("\n" + q[center[0]]);   
         }
     }
 }
 