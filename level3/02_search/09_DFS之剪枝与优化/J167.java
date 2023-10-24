/*
    DFS + 剪枝
    首先枚举大木棒的长度length，然后枚举每根大木棒，看他可以由那些小木棒所拼成

    剪枝:
    1. 小木棒总长为sum,所以枚举的length必须是sum的因子
    2. 优化搜索顺序: 应该先搜索长的木棒，这样分支数少
    3. 排除等效冗余: 
       3.1 如果当前位置放3，下一个4，下一个放5，下次搜索当前位置放4，如果从最前边开始搜，又会放3，然后放5，产生重复
       这样产生的是排列的方式，我们需要的是组合的方式，因此可以固定一个下标顺序去搜索，可以从小到大的搜，当前放的是第4个木棍，下次就从5开始枚举
       3.2 如果当前位置放第i根木棒返回false，那么后边和这个木棒长度相等的放这里也会失败
       3.3 如果一个木棍放在当前这根大木棍的第一个位置，返回了false，则当前枚举的length无解，直接退出
       假设一个木棍放在第一个位置，返回了false，说明这种情况无解
       如果有其他解,那么这根木棍就会放在之后大木棍的除了第一个位置的其他位置，那么将这根木棍移动到第一个位置，也是有解，与假设矛盾
       3.4 如果一个木棍放在当前这根大木棍的最后一个位置，返回了false，则当前枚举的length无解，直接退出
       假设一个木棍房子啊最后一个位置，返回了false，说明这种情况无解
       如果有其他解，那么这根木棒就会放在之后大木棒的除了最后一个位置的其他位置，那么将这根木棍移动到最后一个位置，有解，与假设矛盾
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;   
import java.util.Arrays;

public class J167 {
    static final int N = 70;
    static Integer[] w = new Integer[N];
    static boolean[] st = new boolean[N];
    static int n, sum, length;

    // 搜第u组，当前组长度为len，从start开始搜
    public static boolean dfs(int u, int len, int start) {
        if (u * length == sum) return true;
        if (len == length) return dfs(u + 1, 0, 0);

        for (int i = start; i < n; i++) {
            if (st[i]) continue;
            if (len + w[i] > length) continue;

            st[i] = true;
            if (dfs(u, len + w[i], i + 1)) return true;
            st[i] = false;

            if (len == 0) return false;
            if (length - w[i] == len) return false;

            int j = i;
            while (j < n && w[j] == w[i]) j++;
            i = j - 1;
        }

        return false;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            sum = 0;
            n = Integer.parseInt(br.readLine());
            if (n == 0) break;
            String str[] = br.readLine().split(" ");
            for (int i = 0; i < n; i++) {
                w[i] = Integer.parseInt(str[i]);
                sum += w[i];
            }
            
            Arrays.fill(st, false);
            Arrays.sort(w, 0, n, (o1, o2) -> o2 - o1);
           
            length = 1;
            while (true) {
                if (sum % length == 0 && dfs(0, 0, 0)) {
                    System.out.println(length);
                    break;
                }
                length++;
            }
        }
    }
}
