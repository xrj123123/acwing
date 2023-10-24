/*
    题目中给出了每个公交车的行驶路线，要求的是换乘几次车，我们可以先求出坐了几次车，减一就是换乘几次
    假如一辆公交车路线为1 3 5, 那么g[1][3] = g[1][5] = g[3][5] = 1, 这样建图即可
    因为边权都是1, 所以可以bfs也可以最短路做
*/

// bfs
/* 
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class J920 {
    static final int N = 510;
    static int[] dist = new int[N];
    static boolean[][] g = new boolean[N][N];
    static int[] q = new int[N];
    static int m, n;

    public static void bfs(){
        Arrays.fill(dist, 0x3f3f3f3f);
        int hh = 0, tt = 1;
        q[hh] = 1;
        dist[1] = 0;
        
        while (hh <= tt) {
            int t = q[hh++];

            for (int i = 1; i <= n; i++) 
                if (g[t][i] && dist[i] > dist[t] + 1){
                    dist[i] = dist[t] + 1;
                    q[tt++] = i;
                }
        }
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        m = Integer.parseInt(str[0]);
        n = Integer.parseInt(str[1]);

        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            for (int j = 0; j < str.length; j++)
                for (int k = j + 1; k < str.length; k++){
                    int a = Integer.parseInt(str[j]);
                    int b = Integer.parseInt(str[k]);
                    g[a][b] = true;
                }
        }

        bfs();
        if (dist[n] == 0x3f3f3f3f) 
            System.out.println("NO");
        else
            System.out.println(Math.max(0, dist[n] - 1));
    }
}
*/

// 最短路
import java.io.*;
import java.util.*;

class J920 {
    static final int N = 510;
    static int[] dist = new int[N];
    static boolean[][] g = new boolean[N][N];
    static boolean[] st = new boolean[N];
    static int m, n;

    public static void spfa(){
        Arrays.fill(dist, 0x3f3f3f3f);
        dist[1] = 0;
        Queue<Integer> q = new LinkedList<>();
        q.offer(1);

        while (!q.isEmpty()) {
            int t = q.poll();
            st[t] = false;

            for (int i = 1; i <= n; i++) {
                if (g[t][i] && dist[t] + 1 < dist[i]){
                    dist[i] = dist[t] + 1;
                    if (!st[i]){
                        st[i] = true;
                        q.offer(i);
                    }
                }
            }
        }
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        m = Integer.parseInt(str[0]);
        n = Integer.parseInt(str[1]);

        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            for (int j = 0; j < str.length; j++)
                for (int k = j + 1; k < str.length; k++){
                    int a = Integer.parseInt(str[j]);
                    int b = Integer.parseInt(str[k]);
                    g[a][b] = true;
                }
        }

        spfa();
        if (dist[n] == 0x3f3f3f3f) 
            System.out.println("NO");
        else
            System.out.println(dist[n] - 1);
    }
}