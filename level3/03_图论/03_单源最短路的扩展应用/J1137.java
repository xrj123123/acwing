import java.io.*;
import java.util.*;

class J1137{
    static int N = 1010, M = 21010;
    static int[] h = new int[N], e = new int[M], ne = new int[M], w = new int[M];
    static int[] dist = new int[N];
    static boolean[] st = new boolean[N];
    static int n, m, s, t, idx;

    static void add(int a, int b, int c){
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static int spfa(){      
        Arrays.fill(dist, 0x3f3f3f3f);
        Queue<Integer> q = new LinkedList<>();
        dist[0] = 0;
        q.offer(0);

        while (!q.isEmpty()) {
            int t = q.poll();
            st[t] = false;

            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (dist[t] + w[i] < dist[j]){
                    dist[j] = dist[t] + w[i];
                    if (!st[j]) {
                        st[j] = true;
                        q.offer(j);
                    }
                }
            }
        }

        if (dist[s] == 0x3f3f3f3f) 
            return -1;
        return dist[s];
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String data = null;
        while ((data = br.readLine()) != null){
            String[] str = data.split(" ");
            n = Integer.parseInt(str[0]);
            m = Integer.parseInt(str[1]);
            s = Integer.parseInt(str[2]);

            idx = 0;
            Arrays.fill(h, -1);
            for (int i = 0; i < m; i++) {
                str = br.readLine().split(" ");
                int x = Integer.parseInt(str[0]);
                int y = Integer.parseInt(str[1]);
                int z = Integer.parseInt(str[2]);
                add(x, y, z);
            }

            t = Integer.parseInt(br.readLine());
            str = br.readLine().split(" ");
            for(int i = 0; i < t; i++) {
                int x = Integer.parseInt(str[i]);
                add(0, x, 0);
            }

            System.out.println(spfa());
        }
    }
}