/*
    一般的动态规划问题都可以看作是图论问题, 动态规划中每个状态都可以看做图论中的每个点, 求最小值就是图论求最短距离, 求最大值即求最远距离
    但是只有拓扑图才可以用dp来做, 拓扑图用dp就是线性递推; 如果不是拓扑图,假如存在环,那么dp是无法解决的
    而这道题中, 显然不是拓扑图, 可能存在环, 因此不能使用dp来做, 也不能使用Dijkstra
    因为Dijkstra保证第一次出队的点一定可以确定最小值, 比如5->6->7->5, 上的权值为8, 6的为7, 7的为3, 那么5的权值会被再次更新为3
    因此只能使用spfa做, 以从1到n的每个点作为中间点, 求出从1到k中可以买入的最小值,然后求出从k到n中可以卖出的最大值, 最大值 - 最小值即为利润
    使用spfa计算从1到所有点的最小值, 然后计算从n到所有点的最大值
*/
import java.io.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class J341 {
    static final int N = 100010, M = 2000010;
    static int[] value = new int[N]; // 每个城市的买卖价格
    static int[] dmin = new int[N], dmax = new int[N];  // 从1号点到每个城市的最小值, 和从i到n的最大值
    static int[] h = new int[N], rh = new int[N], e = new int[M], ne = new int[M]; 
    static int n, m, idx;

    static void add(int[] h, int a, int b) {
        e[idx] = b;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    // type为true是找最小值
    static void spfa(int start, int[] h, int[] d, boolean type) {
        boolean[] st = new boolean[N];
        Queue<Integer> q = new LinkedList<>();
        if (type) 
            Arrays.fill(d, 0x3f3f3f3f);
        d[start] = value[start];
        q.offer(start);
        st[start] = true;

        while (!q.isEmpty()) {
            int t = q.poll();
            st[t] = false;

            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (type && d[j] > Math.min(d[t], value[j]) || !type && d[j] < Math.max(d[t], value[j])){
                    if (type)
                        d[j] = Math.min(d[t], value[j]);
                    else
                        d[j] = Math.max(d[t], value[j]);
                    if (!st[j]) {
                        st[j] = true;
                        q.offer(j);
                    }
                }
            }
        } 
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);

        str = br.readLine().split(" ");
        for (int i = 1; i <= n; i++)
            value[i] = Integer.parseInt(str[i - 1]);

        Arrays.fill(h, -1);
        Arrays.fill(rh, -1);
        while (m-- > 0) {
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int y = Integer.parseInt(str[1]);
            int z = Integer.parseInt(str[2]);
            add(h, x, y);
            add(rh, y, x);
            if (z == 2) {
                add(h, y, x);
                add(rh, x, y);
            }
        }
        
        spfa(1, h, dmin, true);
        spfa(n, rh, dmax, false);

        int res = 0;
        for (int i = 1; i <= n; i++)
            res = Math.max(res, dmax[i] - dmin[i]);
        System.out.println(res);
    }
}
