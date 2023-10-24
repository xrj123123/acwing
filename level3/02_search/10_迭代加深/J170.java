/*
    迭代加深: 当某些分支很深,但是答案在一个很浅的分支里时,有时搜索会搜索到很深的分支,大大浪费时间,这时就用到迭代加深
    第一次搜一层,搜不到答案,搜两层,还搜不到,搜三层,以此类推

    本题中, 最大深度有可能达到100层,但是最优答案在8层以内,2^7=128 > 100, 所以可以使用迭代加深来做
    剪枝: 1.每次枚举较大的数   2.排除等效冗余, 枚举当前数字时, 1+4 和 2+3 都是5, 所以可以对枚举出来的数字用一个st数组判重
 */

import java.io.*;
import java.util.*;

public class J170 {
    static final int N = 110;
    static int[] path = new int[N];
    static boolean[] st = new boolean[N];
    static int n;

    public static boolean dfs(int u, int depth) {
        if (u > depth) return false;
        if (path[u - 1] == n) return true;

        // st数组针对的是每一层的dfs，仅保证在下边两层循环枚举当前填的数字时不能重复,对后边的dfs没有影响,因为后边dfs枚举的数字必须比当前的大
        Arrays.fill(st, false);
        for (int i = u - 1; i >= 0; i--)
            for (int j = i; j >= 0; j--) {
                int s = path[i] + path[j];
                if (s > n || s <= path[u - 1] || st[u]) continue;

                st[s] = true;
                path[u] = s;
                if (dfs(u + 1, depth)) return true;
            }

        return false;
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        while ((n = Integer.parseInt(br.readLine())) != 0) {
            int depth = 1;
            path[0] = 1;

            // 搜不到答案就将深度+1
            while (!dfs(1, depth)) depth++;

            for (int i = 0; i < depth; i++)
                System.out.print(path[i] + " ");
            System.out.println();
        }
    }
}
