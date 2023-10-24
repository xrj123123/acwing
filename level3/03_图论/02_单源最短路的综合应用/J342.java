/*
    拓扑排序 + 堆优化Dijkstra
    题目中，道路是双向的，边权非负。航线是单向的，边权可正可负，由于spfa会被卡，所以需要用其他方法
    首先将图构建出来，因此题目中说明如果航线是从A到B，那么不存在任何路径从B到A，将用道路相连的所有点看做一个团，航线连接所有的团
    团与团之间就构成一个拓扑图，因此对于团内做一个Dijkstra，团之间做拓扑排序即可。
    算法流程: 
        1. 先输入所有双向道路, 用id[]表示每个点属于哪个团, 用List<Integer>[] block表示第i个团有哪些点
        2. 输入所有航线, 统计出每个团的入度
        3. 按照拓扑排序处理每个连通块, 首先将入度为0的团的id加入队列
        4. 从队头取出1个元素【入度为0的团的id】, 将block[id]中所有点跑一遍Dijkstra
        5. Dijkstra中, 每次找出dist最小的点t, 枚举这个点的临边j
           如果id[t] == id[j], 表示这两个点在一个团内, 如果j可以被t更新,就将j加入堆中 
           如果id[t] != id[j], 说明这两个点不在一个团内, 就将id[j]所在团的入度-1, 如果入度为0, 就将这个团的id入队
*/

import java.io.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;

@SuppressWarnings("unchecked")
public class J342 {
    static final int N = 25010, M = 150010, INF = 0x3f3f3f3f;
    static int[] id = new int[N];  // id[i]表示第i个城镇属于哪个团
    static List<Integer>[] block = new ArrayList[N]; // block[i]中存储的是第id为i的所有城镇
    static int[] du = new int[N]; // du[i]表示第i个团的入度
    static Queue<Integer> q = new LinkedList<>(); // q模拟队列做拓扑排序
    static int[] dist = new int[N];
    static int[] h = new int[N], e = new int[M], w = new int[M], ne = new int[M];
    static int idx, bcnt;
    static int n, mr, mp, s;

    public static void add(int a, int b, int c){
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    public static void dfs(int u, int bid){
        id[u] = bid;
        block[bid].add(u);

        for (int i = h[u]; i != -1; i = ne[i]){
            int j = e[i];
            if (id[j] == 0)
                dfs(j, bid);
        }

    }

    public static void topsort(){
        Arrays.fill(dist, 0x3f3f3f3f);
        dist[s] = 0;
        // 将入度为0的团的id入队
        for (int i = 1; i <= bcnt; i++){
            if (du[i] == 0)
                q.offer(i);
        }
        while (!q.isEmpty()) {
            int t = q.poll();
            Dijkstra(t);
        }
    }

    public static void Dijkstra(int t){
        boolean[] st = new boolean[N];
        PriorityQueue<PII> heap = new PriorityQueue<>((o1, o2) -> o1.dist - o2.dist);
        // 首先将id为t的所有元素加入堆中
        for (int u : block[t]){
            heap.offer(new PII(dist[u], u));
        }

        // 做Dijkstra
        while (!heap.isEmpty()){
            PII u = heap.poll();
            int ver = u.x;
            if (st[ver]) continue;
            st[ver] = true;

            for (int i = h[ver]; i != -1; i = ne[i]) {
                int j = e[i];
                if (dist[j] > dist[ver] + w[i]){
                    dist[j] = dist[ver] + w[i];
                    if (id[ver] == id[j])
                        heap.offer(new PII(dist[j], j));  
                }
                // 如果j和ver所属的团不同, 那么id[j]的入度-1,, 如果减为0, 就入队
                if (id[ver] != id[j] && --du[id[j]] == 0)
                    q.offer(id[j]);
            }
        }
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        mr = Integer.parseInt(str[1]);
        mp = Integer.parseInt(str[2]);
        s = Integer.parseInt(str[3]);

        for (int i = 0; i < N; i++)
            block[i] = new ArrayList<>();

        Arrays.fill(h, -1);
        // 读入道路
        while (mr-- > 0) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            int c = Integer.parseInt(str[2]);
            add(a, b, c);
            add(b, a, c);
        }

        // dfs搜索每个团
        for (int i = 1; i <= n; i++) {
            if (id[i] == 0) {
                bcnt++;
                dfs(i, bcnt);
            }
        }


        // 读入航线
        while (mp-- > 0) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[0]);
            int b = Integer.parseInt(str[1]);
            int c = Integer.parseInt(str[2]);
            add(a, b, c);
            du[id[b]]++;
        }

        topsort();

        for (int i = 1; i <= n; i++) {
            if (dist[i] > INF / 2) 
                System.out.println("NO PATH");
            else
                System.out.println(dist[i]);
        }
    }
}

class PII{
    int dist;
    int x;
    public PII(int dist, int x){
        this.dist = dist;
        this.x = x;
    }
}
