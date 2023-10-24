/*
    每个时间段合格的收银员数用nums[i]表示，每个时间选取的收银员为xi个，每个时间的清单数为ri
    ① 0 <= xi <= nums[i]
    ② x(i-7)+x(i-6)+...+x(i) >= ri
    由②式可以看出需要使用前缀和，我们用si表示前i个时间段里选择的收银员数，同时使下标从1开始
    ① 0 <= si - s(i-1) <= nums[i] 
        si >= s(i-1)
        s(i-1) >= si - nums[i]
    ② i>=8，si - s(i-8) >= ri
        si >= s(i-8) + ri
    ③ i<8，si + s24 - s(16+i) >= ri
        si >= s(16+i) - s24 + ri
    对于前三个不等式，我们都可以建边，但是对于最优一个不等式，有三个变量，我们无法建边，但是根据题目可知，N的范围为1000，所以s24的范围也是0-1000
    我们可以通过枚举s24的值来建最后一条边，这时s24就是一个常量了
    s24 = c需要建边
    s24 >= c + s0  
    s24 <= c + s0  == > s0 >= s24 -c
*/

import java.io.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class J393 {
    static final int N = 30, M = 100;
    static int[] h = new int[N], e = new int[M], ne = new int[M], w = new int[M];
    static int[] dist = new int[N], r = new int[N], nums = new int[N], cnt = new int[N];
    static boolean[] st = new boolean[N];
    static int n, idx;

    static void add(int a, int b, int c) {
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    // c是s24的取值
    static void build(int c) {
        add(0, 24, c);
        add(24, 0, -c);
        for (int i = 1; i <= 24; i++) {
            add(i - 1, i, 0);
            add(i, i - 1, -nums[i]);
        }

        for (int i = 8; i <= 24; i++)
            add(i - 8, i, r[i]);
        
        for (int i = 1; i <= 7; i++) {
            add(16 + i, i, -c + r[i]);
        }
    }

    static boolean spfa(int c) {
        Arrays.fill(h, -1);
        Arrays.fill(st, false);
        Arrays.fill(cnt, 0);
        Arrays.fill(dist, -0x3f3f3f3f);
        idx = 0;
        build(c);

        Queue<Integer> q = new LinkedList<>();
        q.offer(0);
        st[0] = true;
        dist[0] = 0;
        while (!q.isEmpty()) {
            int t = q.poll();
            st[t] = false;

            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (dist[j] < dist[t] + w[i]) {
                    dist[j] = dist[t] + w[i];
                    cnt[j] = cnt[t] + 1;
                    if (cnt[j] >= 25)
                        return false;
                    if (!st[j]) {
                        st[j] = true;
                        q.offer(j);
                    }
                }
            }
        }
        return true;
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int k = Integer.parseInt(br.readLine());
        for (int cases = 0; cases < k; cases++) {
            String[] str = br.readLine().split(" ");
            for (int i = 1; i <= 24; i++)
                r[i] = Integer.parseInt(str[i - 1]);
        
            n = Integer.parseInt(br.readLine());
            Arrays.fill(nums, 0);
            for (int i = 0; i < n; i++) {
                int t = Integer.parseInt(br.readLine());
                nums[t + 1]++;
            }
            
            boolean flag = false;
            for (int i = 0; i <= 1000; i++) {
                if (spfa(i)) {
                    System.out.println(i);
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                System.out.println("No Solution");
            }
        }
    }
}
