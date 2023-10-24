/*
    01分数规划
    1、建图。最简单的建图方式是，将每个字符串看做一个点，如果字符串A的尾可以和字符串B的首相连，那么就建一条从A到B的边
    这样建图点数最多为1e5，边数假设所有字符串都相同，那么最多为1e5*1e5=1e10条边，空间显然不够，因此需要换种建图方式
    对于字符串abcde，我们可以将前两个字母ab看做一个点，最后两个字母de看做一个点，建一条从ab到de的边，边权为5
    这样点的个数最多为26*26=576，边的个数最多为1e5
    2、求的是∑w[i]/∑1的最大值，直接用01分数规划。题目中答案最小值大于0，最大值为1000，取一个mid，如果∑w[i]/∑1>mid, 那么l=mid, 否则r=mid
    ∑w[i] / ∑1 > mid --> ∑w[i] > mid∑1 --> ∑w[i] - mid∑1 > 0 --> ∑(w[i] - mid) > 0，即将边权改为w[i]-mid，判断是否存在正环。
    对于无解情况：无解表示题目中不存在环，因此mid=0代入，只要没有环，就无解
    3、优化，直接这么做会tle，spfa判断负环有一个经验值，即所有经过的边权数大于2*n就可以判断存在负环，正环也一样
*/

import java.io.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class J1165 {
    static final int N = 700, M = 100010;
    static int[] h = new int[N], e = new int[M], w = new int[M], ne = new int[M];
    static double[] dist = new double[N];
    static int[]cnt = new int[N];
    static boolean[] st = new boolean[N];
    static int n, idx;

    static void add(int a, int b, int c) {
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static boolean check(double mid) {
        Queue<Integer> q = new LinkedList<>();
        Arrays.fill(cnt, 0);
        for (int i = 0; i < 676; i++) {
            q.offer(i);
            st[i] = true;
        }
        
        int count = 0;
        while (!q.isEmpty()) {
            int t = q.poll();
            st[t] = false;

            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (dist[j] < dist[t] + w[i] - mid) {
                    dist[j] = dist[t] + w[i] - mid;
                    cnt[j] = cnt[t] + 1;
                    if (++count > 2 * n)
                        return true;
                    if (cnt[j] >= N) 
                        return true;
                    if (!st[j]) {
                        q.offer(j);
                        st[j] = true;
                    }
                }
            }
        }
        return false;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            Arrays.fill(h, -1);
            idx = 0;
            n = Integer.parseInt(br.readLine());
            if (n == 0)
                break;
            
            for (int i = 0; i < n; i++) {
                char[] s = br.readLine().toCharArray();
                int len = s.length;
                if (len >= 2) {
                    int left = (s[0] - 'a') * 26 + (s[1] - 'a');
                    int right = (s[len - 2] - 'a') * 26 + (s[len - 1] - 'a');
                    add(left, right, len);
                }
            }
            
            if (!check(0))
                System.out.println("No solution");
            else {
                double l = 0, r = 1000;
                while (r - l > 1e-4) {
                    double mid = (l + r) / 2;
                    if (check(mid))
                        l = mid;
                    else
                        r = mid;
                }
                System.out.println(l);
            }
        }
    }

}
