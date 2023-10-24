/*
    双向DFS
    题目和背包问题一样，但是本题N是小于46，W是2^31-1，是背包做会超时
    N只有46，所以可以直接dfs枚举所有情况，时间复杂度为2^46，显然超时

    所以可以使用双向dfs，对于前一半的数，我们可以dfs枚举可以得到的数字并存在数组中
    然后dfs后一半的数，每次枚举到一个数字后s，就在数组中找到一个小于等于w-s的最大的数，这里使用二分，枚举所有情况，找到小于等于w的最大值
    时间复杂度，前一半枚举+排序: 枚举时间复杂度为2^23, 排序时间复杂度nlogn, 23*2^23, 后一半枚举+二分: 2^23*logn = 2^23 * 23

    剪枝: 
    1.每次dfs时枚举较大的数，这样分支数会少，并且会很快出现大于w的情况，直接continue掉
 */

import java.io.*;
import java.util.*;

class J171 {
    static final int N = 46;
    static int m, n, cnt, res;
    static Integer[] w = new Integer[N], weight = new Integer[1 << (N / 2)];

    public static void dfs1(int u, int s){
        if (u == n / 2) {
            weight[cnt++] = s;
            return;
        }

        dfs1(u + 1, s);
        if ((long)s + w[u] <= m) 
            dfs1(u + 1, s + w[u]);
    }

    public static void dfs2(int u, int s){
        if (u == n) {
            int l = 0, r = cnt - 1;
            while (l < r) {
                int mid = l + r + 1 >> 1;
                if (weight[mid] <= m - s)
                    l = mid;
                else
                    r = mid - 1;
            }
            res = Math.max(res, s + weight[l]);
            return;
        }

        dfs2(u + 1, s);
        if ((long)s + w[u] <= m)
            dfs2(u + 1, s + w[u]);
    }

    public static void unique(){
        int idx = 0;
        for (int i = 0; i < cnt; i++) {
            if (i == 0 || weight[i] != weight[i - 1])
                weight[idx++] = weight[i];
        }
        cnt = idx;
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));   
        String[] str = br.readLine().split(" ");
        m = Integer.parseInt(str[0]);
        n = Integer.parseInt(str[1]);

        for (int i = 0; i < n; i++)
            w[i] = Integer.parseInt(br.readLine());
        
        Arrays.sort(w, 0, n, (o1, o2) -> o2 - o1);

        dfs1(0, 0);

        // 对weight排序去重
        Arrays.sort(weight, 0, cnt);
        unique();

        dfs2(n / 2, 0);

        System.out.println(res);
    }
}