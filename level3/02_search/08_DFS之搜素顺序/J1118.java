import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class J1118 {
    static final int N = 12;
    static int[] nums = new int[N];
    static List<ArrayList<Integer>> group = new ArrayList<>();
    static int n, res;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(br.readLine());
        String str[] = br.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            group.add(new ArrayList<>());
            nums[i] = Integer.parseInt(str[i]);
        }
            
        res = n;
        dfs(0, 1);
        System.out.println(res);
    }

    public static int gcd(int a, int b) {
        return b > 0 ? gcd(b, a % b) : a;
    }

    // 判断第i个数能否放入g中
    public static boolean check(ArrayList<Integer> g, int x) {
        for (int j = 0; j < g.size(); j++) {
            if (gcd(g.get(j), x) > 1) 
                return false;
        }
        return true;
    }

    // 第u个数, 一共g组
    public static void dfs(int u, int g){
        // 当前组数比res大, 直接返回
        if (g >= res) return;

        if (u >= n) 
            res = Math.min(res, g);
            
        // 看可以将第u个数放到那一组
        for (int i = 0; i < g; i++) {
            if (check(group.get(i), nums[u])) {
                group.get(i).add(nums[u]);
                dfs(u + 1, g);
                group.get(i).remove(group.get(i).size() - 1);
            }
        }

        // 新开一组将u放入
        if (g + 1 <= n) {
            group.get(g).add(nums[u]);
            dfs(u + 1, g + 1);
            group.get(g).remove(group.get(g).size() - 1);
        }
    }
}
