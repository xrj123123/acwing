/*
    双向BFS
    因为最多有6种变换规则,字符串长度最多为20，所以一个字符串每次扩展的状态最多有120种,最多走10步，也就是120^10,要么mle,要么tle【每次扩展指数级增加】
    所以可以采用双向BFS，从起点和终点一起往中间搜，如果相遇就结束
    但需要注意的是，双向BFS搜索时，每次不是扩展一个点，而是扩展一层。
    假如一次扩展一个点，当a扩展一次后，变为x+1次，没搜到，去扩展b，b扩展一次变为y+1次，然后搜索到a扩展后状态，这样总次数就是x+y+2
    但是存在一种情况，a后边一个状态，和a步数相同，扩展一次就出现b中的状态，那么总次数就是x+y+1，所以要一层一层扩展
    根据队列的单调性和二段性可知，一层一层扩展也就是当a这边扩展完之后，a中所有状态步数是相同的，然后去b扩展，扩展b时，如果发现在a存在，就直接返回
 */

 import java.io.*;
 import java.util.*;
 
 public class J190 {
     static final int N = 6;
     static int n;
     static String[] a = new String[N], b = new String[N]; // 变换规则
     static String A, B;
     static Queue<String> qa = new LinkedList<>(), qb = new LinkedList<>();
     static Map<String, Integer> da = new HashMap<>(), db = new HashMap<>(); 
     public static void main(String[] args) throws IOException{
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
         String[] str = br.readLine().split(" ");
         A = str[0]; 
         B = str[1];
         String data;
         while ((data = br.readLine()) != null) {
             str = data.split(" ");
             a[n] = str[0];
             b[n++] = str[1];   
         }
 
         int t = bfs(A, B);
         if (t == -1) System.out.println("NO ANSWER!");
         else System.out.println(t);
     }
 
     public static int extend(Queue<String> q, Map<String, Integer> da, Map<String, Integer> db, String[] a, String[] b) {
         int d = da.get(q.peek());
 
         while (q.size() > 0 && da.get(q.peek()) == d) {
             String s = q.poll();
             for (int i = 0; i < n ; i++) 
                 for (int j = 0; j < s.length(); j++) {
                     if (j + a[i].length() <= s.length() && s.substring(j, j + a[i].length()).equals(a[i])) {
                         String r = s.substring(0, j) + b[i] + s.substring(j + a[i].length());
                         if (db.containsKey(r)) return da.get(s) + db.get(r) + 1;
                         if (da.containsKey(r)) continue;
                         da.put(r, d + 1);
                         q.offer(r);
                     }
                 }
         }
         return 11;
     }
 
     public static int bfs(String A, String B) {
         if (A.equals(B)) return 0;
         qa.offer(A);
         qb.offer(B);
         da.put(A, 0);
         db.put(B, 0);
 
         while (qa.size() > 0 && qb.size() > 0) {
             int t = 0, step = 0;
             if (qa.size() <= qb.size()) t = extend(qa, da, db, a, b);
             else t = extend(qb, db, da, b, a);
             
             if (t <= 10) return t;
             if (++step >= 10) return -1;
         }
 
         return -1;
     }
 }
 