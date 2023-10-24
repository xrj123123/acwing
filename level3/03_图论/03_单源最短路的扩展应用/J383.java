/*
    在最短路计数那道题中, 我们只需要计算最短路的条数, 而这道题还需要计算次短路的条数, 最短路使用bfs和dijkstra是满足拓扑序的, 而次短路也是满足的
    因此就和拯救大兵瑞恩这道题一样, 需要将每个点的状态细化, 对于每个点来说, 他有两种状态
    dist[i][0]表示从起点到i的最短路, dist[i][1]表示从起点到i的次短路
    cnt[i][0]表示从起点到i的最短路的条数, cnt[i][1]表示从起点到i的次短路条数

    使用Dijkstra时, 每次出队的点, 一定是当前距离起点最近的, 对于他可以更新的点j
    如果dist[j][0] > dist[t][type], 那么更新最短路, 最短路入队, 同时更新次短路, 次短路入队
    如果dist[j][0] == dist[t][type], cnt[j][0] += cnt[t][type]
    如果dist[j][1] > dist[t][type], 那么更新次短路, 次短路入队
    如果dist[j][1] == dist[t][type], cnt[j][1] += cnt[t][type]
*/

import java.io.*;
import java.util.*;

public class J383 {
    static final int N = 1010, M = 10010;
    static int[][] dist = new int[N][2], cnt = new int[N][2];
    static boolean[][] st = new boolean[N][2];
    static int[] h = new int[N], e = new int[M], w = new int[M], ne = new int[M];
    static int n, m, s, f, idx;

    static void add(int a, int b, int c){
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static int Dijkstra(){
        for (int i = 0; i < N; i++){
            Arrays.fill(dist[i], 0x3f3f3f3f);
            Arrays.fill(cnt[i], 0);
            Arrays.fill(st[i], false);
        }    
        dist[s][0] = 0;
        cnt[s][0] = 1;
        PriorityQueue<PIII> q = new PriorityQueue<>((o1, o2) -> (o1.dis - o2.dis));
        q.offer(new PIII(s, 0, 0));

        while (!q.isEmpty()) {
            PIII t = q.poll();
            int ver = t.x;
            int type = t.type;
            if (st[ver][type])
                continue;
            st[ver][type] = true;
            for (int i = h[ver]; i != -1; i = ne[i]){
                int j = e[i];
                if (dist[j][0] > dist[ver][type] + w[i]) {
                    dist[j][1] = dist[j][0];
                    cnt[j][1] = cnt[j][0];
                    q.offer(new PIII(j, 1, dist[j][1]));
                    dist[j][0] = dist[ver][type] + w[i];
                    cnt[j][0] = cnt[ver][type];
                    q.offer(new PIII(j, 0, dist[j][0]));
                }else if (dist[j][0] == dist[ver][type] + w[i]){
                    cnt[j][0] += cnt[ver][type];
                }else if (dist[j][1] > dist[ver][type] + w[i]) {
                    dist[j][1] = dist[ver][type] + w[i];
                    cnt[j][1] = cnt[ver][type];
                    q.offer(new PIII(j, 1, dist[j][1]));
                }else if (dist[j][1] == dist[ver][type] + w[i]){
                    cnt[j][1] += cnt[ver][type];
                }
            }
        }

        int res = cnt[f][0];
        if (dist[f][0] + 1 == dist[f][1])
            res += cnt[f][1];
        return res;
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        for (int i = 0; i < t; i++){
            String[] str = br.readLine().split(" ");
            n = Integer.parseInt(str[0]);
            m = Integer.parseInt(str[1]);

            idx = 0;
            Arrays.fill(h, -1);
            for (int j = 0; j < m; j++){
                str = br.readLine().split(" ");
                int x = Integer.parseInt(str[0]);
                int y = Integer.parseInt(str[1]);
                int z = Integer.parseInt(str[2]);
                add(x, y, z);
            }

            str = br.readLine().split(" ");
            s = Integer.parseInt(str[0]);
            f = Integer.parseInt(str[1]);
            
            System.out.println(Dijkstra());
        }
    }
}

class PIII{
    int x;
    int type;
    int dis;
    public PIII(int x, int type, int dis){
        this.x = x;
        this.type = type;
        this.dis = dis;
    }
}
