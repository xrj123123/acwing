import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class J802 {
    static final int N = 300010;
    static int[] a = new int[N], s = new int[N];
    static List<PII> add = new ArrayList<>(), query = new ArrayList<>();
    static List<Integer> alls = new ArrayList<>();
    static int n, m;

    static int find(int x) {
        int l = 0, r = alls.size() - 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (alls.get(mid) >= x) 
                r = mid;
            else
                l = mid + 1;
        }
        return l + 1;   // 让下标为1-n，方便求前缀和
    }

    static int unique() {
        int j = 0;
        for (int i = 0; i < alls.size(); i++) {
            if (i == 0 || alls.get(i) != alls.get(i - 1)) {
                alls.set(j++, alls.get(i));
            }
        }
        return j;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);

        for (int i = 0; i < n; i++) {
            str = br.readLine().split(" ");
            int x = Integer.parseInt(str[0]);
            int c = Integer.parseInt(str[1]);
            add.add(new PII(x, c));
            alls.add(x);
        }

        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int l = Integer.parseInt(str[0]);
            int r = Integer.parseInt(str[1]);
            alls.add(l);
            alls.add(r);
            query.add(new PII(l ,r));
        }

        Collections.sort(alls);
        int j = unique();
        alls = alls.subList(0, j);

        for (PII t : add) {
            int x = find(t.x);
            int c = t.y;
            a[x] += c;
        }

        for (int i = 1; i <= alls.size(); i++) {
            s[i] = s[i - 1] + a[i];
        }

        for (PII t : query) {
            int l = find(t.x);
            int r = find(t.y);
            System.out.println(s[r] - s[l - 1]);
        }
    }
}

class PII {
    int x, y;
    public PII(int x, int y) {
        this.x = x;
        this.y = y;
    }
}
