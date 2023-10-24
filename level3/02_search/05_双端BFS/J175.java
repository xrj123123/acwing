/*
    双端队列BFS
    可以将每个方格的通路权值看做0, 不通的权值看做1, 这样就是求从起点到终点的最短路(Dijkstra)
    方格的范围从[0,n-1],但是格点的范围是从[0,n], 也就是求(0, 0)到(n, m)点的最短距离
    可以发现, 图中有一半的点是无法走到的,因为起点为(0,0),每次斜着走,x和y方向都会同时加一或减一,所以图中奇数格点是无法走到的
    用bfs来做,由于bfs的两段性和单调性可知,从队头取出的元素一定是最小值
    所以从队头取出一个元素后,由该元素进行扩展,如果扩展的路径权值为0,那么插入队头,如果为1,就插入队尾. 这样保证了队列的两段性和单调性
 */

 import java.io.*;
 import java.util.*;;
 
 public class J175 {
     // dx,dy是从当前这个点走到周围的四个点. ix,iy是当前这个点到周围四个点需要经过的格子的坐标
     static int[] dx = {-1, -1, 1, 1}, dy = {-1, 1, 1, -1};
     static int[] ix = {-1, -1, 0, 0}, iy = {-1, 0, 0, -1};
     static char cs[] = {'\\', '/', '\\', '/'}; 
     static final int N = 510;
     static char[][] g = new char[N][N];
     static boolean[][] st = new boolean[N][N]; // st表示当前点是否计算完毕,和Dijkstra一样,只有出队时才可以确定当前点的最小值,每个点可能被更新多次
     static int[][] dist = new int[N][N];
     static int n, m;
     public static void main(String[] args) throws IOException{
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
         int T = Integer.parseInt(br.readLine());
         while (T-- > 0) {
             String[] str = br.readLine().split(" ");
             n = Integer.parseInt(str[0]);
             m = Integer.parseInt(str[1]);
 
             for (int i = 0; i < n; i++) {
                 String s = br.readLine();
                 for (int j = 0; j < m; j++)
                     g[i][j] = s.charAt(j);
             }
 
             if (((n + m) & 1) != 0) System.out.println("NO SOLUTION");
             else System.out.println(bfs());
         }
     }
 
     public static int bfs() {
         for (int i = 0; i <= n; i++) {
             Arrays.fill(st[i], false);
             Arrays.fill(dist[i], 0x3f3f3f3f);
         }
         Deque<PII> q = new LinkedList<>();
         q.offerLast(new PII(0, 0));
         dist[0][0] = 0;
 
         while (q.size() > 0) {
             PII t = q.pollFirst();
             int x = t.x;
             int y = t.y;
             if (x == n && y == m) return dist[n][m];
             st[x][y] = true; 
 
             for (int i = 0; i < 4; i++) {
                 int a = x + dx[i];
                 int b = y + dy[i];
                 int ga = x + ix[i];
                 int gb = y + iy[i];
                 if (a < 0 || a > n || b < 0 || b > m) continue;
                 if (st[a][b]) continue;
 
                 int w = g[ga][gb] == cs[i] ? 0 : 1;
                 int d = dist[x][y] + w;
                 if (d < dist[a][b]) {
                     dist[a][b] = d;
                     if (w == 0)
                         q.offerFirst(new PII(a, b));
                     else
                         q.offerLast(new PII(a, b));
                 }
             }
         }
         return -1;
     }
 }
 
 class PII{
     int x;
     int y;
     public PII(int x, int y) {
         this.x = x;
         this.y = y;
     }
 }
 