// acwing 1107 魔板
/*
    按A B C的操作顺序依次入队，最终就是字典序最小
*/
 
import java.io.*;
import java.util.*;
public class J1107 {
    static char[][] g = new char[2][4];
    static String start = "", end = "";
    static Queue<String> q = new LinkedList<>(); // 队列，用于bfs
    static Map<String, Integer> dist = new HashMap<>(); // dist[i]=j表示从start到i状态走了j步
    static Map<String, P> pre = new HashMap<>(); // 存上一个状态

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] nums = br.readLine().split(" ");
        for (int i = 0; i < 8; i++) {
            end += nums[i];
        }
            
        for (int i = 1; i <= 8; i++){
            start += (char)(i + '0');
        }

        bfs(start, end);

        System.out.println(dist.get(end));

        String res = "";
        while (!end.equals(start)) {
            res += pre.get(end).s;
            end = pre.get(end).state;
        }
        
        if (res.length() > 0){
            for (int i = res.length() - 1; i >= 0; i--)
                System.out.print(res.charAt(i));
            System.out.println();
        }

        br.close();
    }

    // 将state转为二维数组
    public static void set(String state) {
        for (int i = 0; i < 4; i++) g[0][i] = state.charAt(i);
        for (int i = 3, j = 4; i >= 0; i--, j++) g[1][i] = state.charAt(j);
    }

    // 将二维数组转为String
    public static String get() {
        String res = "";
        for (int i = 0; i < 4; i++) res += g[0][i];
        for (int i = 3; i >= 0; i--) res += g[1][i];
        return res;
    }

    public static String move0(String state) {
        set(state);
        for (int i = 0; i < 4; i++) {
            char t = g[0][i];
            g[0][i] = g[1][i];
            g[1][i] = t; 
        }
        return get();
    }

    public static String move1(String state) {
        set(state);
        char v0 = g[0][3], v1 = g[1][3];
        for (int i = 3; i > 0; i--) {
            g[0][i] = g[0][i - 1];
            g[1][i] = g[1][i - 1];
        }
        g[0][0] = v0;
        g[1][0] = v1;
        return get();
    }

    public static String move2(String state) {
        set(state);
        char v = g[0][1];
        g[0][1] = g[1][1];
        g[1][1] = g[1][2];
        g[1][2] = g[0][2];
        g[0][2] = v;
        return get();
    }

    public static void bfs(String start, String end) {
        if (start == end) return;
        q.offer(start);
        dist.put(start, 0);

        while (q.size() > 0) {
            String t = q.poll();

            String[] m = new String[3];
            m[0] = move0(t);
            m[1] = move1(t);
            m[2] = move2(t);

            for (int i = 0; i < 3; i++) {
                String str = m[i];
                
                if (dist.containsKey(str)) continue;
                
                int d = dist.get(t);
                dist.put(str, d + 1);
                q.offer(str);
                pre.put(str, new P((char)(i + 'A'), t));
                if (str == end)
                    return;
            }
        }
    }
}

class P {
    char s;
    String state;
    public P(char s, String state) {
        this.s = s;
        this.state = state;
    }
}