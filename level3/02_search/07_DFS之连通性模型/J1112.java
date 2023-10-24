import java.io.*;
import java.util.*;

class J1112{
    static final int N = 110;
    static int sx, sy, ex, ey, n;
    static int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
    static char[][] g = new char[N][N];
    static boolean[][] st = new boolean[N][N];
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int k = Integer.parseInt(br.readLine());
        while (k-- > 0) {
            n = Integer.parseInt(br.readLine());
            for (int i = 0; i < n; i++)
                Arrays.fill(st[i], false);
            
            for (int i = 0; i < n; i++) {
                String s = br.readLine();
                for (int j = 0; j < n; j++)
                    g[i][j] = s.charAt(j);
            }

            String[] str = br.readLine().split(" ");
            sx = Integer.parseInt(str[0]);
            sy = Integer.parseInt(str[1]);
            ex = Integer.parseInt(str[2]);
            ey = Integer.parseInt(str[3]);

            if (dfs(sx, sy)) System.out.println("YES");
            else System.out.println("NO");
        }
    }

    public static boolean dfs(int x, int y) {
        if (g[x][y] == '#') return false;
        if (x == ex && y == ey) return true;

        /* 
            这里不需要回溯，对于内部搜索，不需要回溯。对于一个状态变为另一个状态，需要回溯
            假设现在搜索到了(x,y)，然后这个点会向四周进行搜索
            如果这个点无法返回true，说明他向四个方向搜索后都无法达到终点，那么从其他点经过这个点也无法到达终点。所以就没必要继续搜了，也就不需要回溯
        */
        st[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx < 0 || tx >= n || ty < 0 || ty >= n) continue;
            if (st[tx][ty]) continue;
            if (dfs(tx, ty)) return true;
        }

        return false;
    }
}

