/*
    DFS剪枝:
    1. 优化搜索顺序。大部分情况下，我们应该优先搜索分支较少的节点
    2. 排除等效冗余
    3. 可行性优化
    4. 最优性优化
    5. 记忆化搜索(dp)

    对于本题，n个小猫，要求将n个小猫放到最少数量的缆车上送下去。
    对于每只小猫，我们可以枚举现在有的所有缆车，看他可以放到哪一个缆车上，可以放就放上去，然后dfs。或者另开一个新的缆车，将他放上去进行dfs
    当枚举了n只小猫时，我们就结束搜索，然后求最小值

    对于本题的搜索顺序，我们可以先将重量大的猫放到缆车上，这样分支数就会少。
    假设现在是第一只猫，现在缆车数量为0，所以就要为这只猫新开一个缆车，将其放上去。
    然后开始放第二只猫，第二只猫有两种放法，和第一只放一起或者另开一个。
    此时如果我们先放重量轻的猫，那么第二只猫就有可能可以和第一只猫放在一起，就会有两种情况，1: 和第一只猫放一起 2: 另开一个缆车放上去。
    第三只猫对于1 就会有两种情况，对于2就会有3种情况，分支会很大。
    但是如果我们先放的是重量大的猫，放了第一只猫后，准备放第二只，此时由于重量大，第二只猫无法和第一只放一起，因此只有再开一个缆车这一种情况
    放第三只猫也是这样，就会大大减少分支数量
 */

import java.io.*;
import java.util.*;

public class J165 {
    static final int N = 20;
    static int n, w, res;
    static Integer[] c = new Integer[N];
    static int[] group = new int[N];
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        w = Integer.parseInt(str[1]);
        for (int i = 0; i < n; i++)
            c[i] = Integer.parseInt(br.readLine());
        Arrays.sort(c, 0, n, (o1, o2) -> o2 - o1);

        res = n;
        dfs(0, 0);
        System.out.println(res);
    }

    public static void dfs(int u, int num) {
        if (num >= res) return;
        if (u == n) {
            res = num;
            return;
        }

        for (int i = 0; i < num; i++) {
            if (group[i] + c[u] <= w) {
                group[i] += c[u];
                dfs(u + 1, num);
                group[i] -= c[u];
            }
        }
        
        group[num] = c[u];
        dfs(u + 1, num + 1);
        group[num] -= c[u];
    }
}
