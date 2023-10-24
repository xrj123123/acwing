/*
    DFS + 剪枝
    对于9×9的棋盘上的空位，我们每次随机取一个空位去填数字,并且该数字满足: 在本行、本列、本方格未出现，
    依次枚举所有可能的数字。枚举完一个空位后,继续枚举下一个空位,直到空位填满

    搜索顺序优化: 对于本题的搜索顺序，我们每次可以先去填充可以放数字较少的空位，这样他的分支也会少
    可行性优化: 我们每次填充的数字，都是在本行、本列、本方格未出现的数字
    二进制优化: 对于每行每列和每个方格,我们可以用一个9位的二进制数字来表示, 该数字的第i位为1表示这个位置可以填充i,为0表示不可以
    对于每个空位,我们让行、列、方块做与运算,与运算的结果中有1的位置就是可以放的数字
    对于求一个数字的二进制数位哪里是1,可以使用lowbit来计算,lowbit(x)计算的是x的最后一位1的值
 */

import java.io.*;

public class J166 {
    static final int N = 9, M = 1 << N;
    static int[] row = new int[N], col = new int[N];
    static int[][] cell = new int[3][3];
    static int[] ones = new int[M], map = new int[M];  // ones[i]表示i的二进制有多少个1, map[i]表示log2i
    static char str[];

    public static void init() {
        for (int i = 0; i < N; i++)
            row[i] = col[i] = (1 << N) - 1;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cell[i][j] = (1 << N) - 1;
    }

    public static int lowbit(int x) {
        return x & -x;
    }

    // x行y列填充/移除数字t
    public static void draw(int x, int y, int t, boolean is_set) {
        if (is_set) str[x * N + y] = (char)('1' + t);
        else str[x * N + y] = '.';

        int v = 1 << t;
        if (!is_set) v = -v;

        row[x] -= v;
        col[y] -= v;
        cell[x / 3][y / 3] -= v;
    }

    public static int get(int x, int y) {
        return row[x] & col[y] & cell[x / 3][y / 3];
    }

    public static boolean dfs(int cnt) {
        if (cnt == 0) return true;

        int minv = 10;
        int x = 0, y = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                if (str[i * N + j] == '.') {
                    int state = get(i, j);
                    if (ones[state] < minv) {
                        minv = ones[state];
                        x = i;
                        y = j;
                    }
                }
            }
        
        int state = get(x, y);
        for (int i = state; i > 0; i -= lowbit(i)) {
            int k = map[lowbit(i)];
            draw(x, y, k, true);
            if (dfs(cnt - 1)) return true;
            draw(x, y, k, false);
        }

        return false;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        for (int i = 0; i < 1 << N; i++)
            for (int j = 0; j < N; j++)
                ones[i] += ((i >> j) & 1);
        for (int i = 0; i < N; i++)
            map[1 << i] = i;

        String data;
        while (!(data = br.readLine()).equals("end")) {
            init();
            str = data.toCharArray();
            int cnt = 0;
            for (int i = 0, k = 0; i < N; i++)
                for (int j = 0; j < N; j++, k++) {
                    if (str[k] != '.') {
                        int t = str[k] - '1';
                        draw(i, j, t, true);
                    }else   
                        cnt++;
                }

            dfs(cnt);
            System.out.println(new String(str));
        }
    }
}