/*
    A*算法
    在模型的状态空间很大时，如果用传统BFS找最小步数，会导致MLE或者TLE，因此可以使用A*算法
    A*算法就是启发式搜索，考虑当前已有代价和到终点的预估代价，因此可以优先扩展整体代价最小的点，可以少扩展许多无用的点
    A*算法基本步骤: 
        1. 用一个优先队列来存(小根堆),将起点入队，队列中存储的是d(u)+f(u) 和 当前状态, d(u)是从起点到u的实际距离,f(u)是从u到终点的估价距离
        2. 每次从队头取出元素进行扩展，将扩展到的元素入队
        3. 直到终点出队才能求出最小值
    使用A*算法的前提是该问题必须有解，如果无解，就和普通bfs一样，搜索全部空间，并且A*使用优先队列，每次入队时间复杂度为logn，比普通bfs时间复杂度还高
    A*算法当终点出队时，可以求出终点到起点的最小步数，且只能求出起点到终点的最小步数，其他点出队不一定是最小步数
    A*算法必须满足f(u) <= g(u)，f(u)是从u到终点的预估代价，g(u)是从u到终点的实际代价

    证明: 为什么终点出队时，为最优解
    设终点出队时的距离为d，假设不是最优解，则 d > d0(最优解)
    当前队列中一定存在一个点u是在最优路径上的【最差是起点】,那么d(u) + f(u) <= d(u)+g(u) = d0，那么d > d0 > d(u)+f(u)，
    即当前出队的应该是u这个点，矛盾，因此终点出队一定是最优解

    对于八数码问题，如果逆序对数量为偶数，则一定有解，如果为奇数则一定无解。
    对于初始状态，如果他的逆序对数量为偶数，那么不管怎么变换，他的逆序对数量都是偶数
    如果左右移动，逆序对数量不变，如果上下移动，只会有两组数据的逆序对改变，因此奇偶性不变
    八数码问题的估价函数用的是哈曼顿距离，即假设当前第3个位置放的数字是5，他的代价就是这个数字5移动到第5个位置所需要走的步数
 */

import java.io.*;
import java.util.*;

public class J179 {
    static String start = "", seq = "";
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        for (int i = 0; i < 9; i++) {
            start += str[i];
            if (!str[i].equals("x"))
                seq += str[i];
        }

        int cnt = 0;
        for (int i = 0; i < 8; i++)
            for (int j = i; j < 8; j++)
                if (seq.charAt(j) > seq.charAt(i))
                    cnt++;
        if ((cnt & 1) == 1) System.out.println("unsolvable");
        else bfs();
    }

    // 估价函数
    public static int f(String state) {
        int ans = 0;

        // i表示该数字当前放的位置，t是应该放的位置
        for (int i = 0; i < 9; i++){
            if (state.charAt(i) != 'x') {
                int t = state.charAt(i) - '1';
                ans += Math.abs(i / 3 - t / 3) + Math.abs(i % 3 - t % 3);
            }
        }
        return ans;
    }

    public static void bfs() {
        String end = "12345678x";
        HashMap<String, Integer> dist = new HashMap<>(); // 存当前状态到起点的距离
        HashMap<String, PCS> pre = new HashMap<>(); // 存当前状态上一个状态和操作
        PriorityQueue<PIS> q = new PriorityQueue<>(new Comparator<PIS>(){ // 存的是距离+估价 和 当前状态
            @Override
            public int compare(PIS p1, PIS p2) {
                return p1.x - p2.x;
            }
        });

        char[] op = {'u', 'r', 'd', 'l'};
        int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

        dist.put(start, 0);
        q.offer(new PIS(f(start), start));

        while (q.size() > 0) {
            PIS t = q.poll();
            String state = t.y;
            if (state.equals(end)) break;
            
            int x = 0, y = 0;
            for (int i = 0; i < 9; i++){
                if (state.charAt(i) == 'x') {
                    x = i / 3;
                    y = i % 3;
                    break;
                }
            }

            String source = state;
            for (int i = 0; i < 4; i++) {
                int a = x + dx[i];
                int b = y + dy[i];
                if (a < 0 || a >= 3 || b < 0 || b >= 3) continue;
                state = source;
                char[] tmp = state.toCharArray();
                char c = tmp[3 * x + y];
                tmp[3 * x + y] = tmp[3 * a + b];
                tmp[3 * a + b] = c;
                state = new String(tmp);
                if (!dist.containsKey(state) || dist.get(state) > dist.get(source) + 1) {
                    dist.put(state, dist.get(source) + 1);
                    pre.put(state, new PCS(op[i], source));
                    q.offer(new PIS(dist.get(state) + f(state), state));
                }
            }

        }

        // 输出
        String res = "";
        while (!end.equals(start)) {
            res += pre.get(end).x;
            end = pre.get(end).y;
        }
        for (int i = res.length() - 1; i >= 0; i--)
            System.out.print(res.charAt(i));
        System.out.println();
    }
}

class PIS{
    int x;
    String y;
    public PIS(int x, String y) {
        this.x = x;
        this.y = y;
    }
}

class PCS{
    char x;
    String y;
    public PCS(char x, String y) {
        this.x = x;
        this.y = y;
    }
}
