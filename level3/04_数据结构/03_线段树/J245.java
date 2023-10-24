import java.io.*;

public class J245 {
    static final int N = 500010;
    static Node[] tr = new Node[4 * N];
    static int[] w = new int[N];
    static int n, m;

    static void pushup(Node u, Node l, Node r) {
        u.sum = l.sum + r.sum;
        u.lmax = Math.max(l.lmax, l.sum + r.lmax);
        u.rmax = Math.max(r.rmax, r.sum + l.rmax);
        u.tmax = Math.max(Math.max(l.tmax, r.tmax), l.rmax + r.lmax);
    }

    static void pushup(int u) {
        pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
    }

    static void build(int u, int l, int r) {
        
        if (l == r) {
            tr[u] = new Node(l, r, w[l], w[l], w[l], w[l]);
            return;
        }
        
        tr[u] = new Node(l, r, 0, 0, 0, 0);
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }

    static void modify(int u, int x, int v){
        if (tr[u].l == x && tr[u].r == x) {
            tr[u] = new Node(x, x, v, v, v, v);
        } else {
            int mid = tr[u].l + tr[u].r >> 1;
            if (x <= mid)
                modify(u << 1, x, v);
            else
                modify(u << 1 | 1, x, v);
            pushup(u);
        }
    }

    static Node query(int u, int l, int r){
        if (tr[u].l >= l && tr[u].r <= r)
            return tr[u];

        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid)
            return query(u << 1, l, r);
        if (l > mid)
            return query(u << 1 | 1, l, r);
        
        Node left = query(u << 1, l, r);
        Node right = query(u << 1 | 1, l, r);
        Node res = new Node(0, 0, 0, 0, 0, 0);
        pushup(res, left, right);

        return res;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);

        str = br.readLine().split(" ");
        for (int i = 1; i <= n; i++)
            w[i] = Integer.parseInt(str[i - 1]);
        
        build(1, 1, n);

        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            int k = Integer.parseInt(str[0]);
            int x = Integer.parseInt(str[1]);
            int y = Integer.parseInt(str[2]);
            
            if (k == 1) {
                if (x > y) {
                    int t = x;
                    x = y;
                    y = t;
                }
                System.out.println(query(1, x, y).tmax);
            } else {
                modify(1, x, y);
            }
        }
    }
}

class Node {
    int l, r;
    int sum, lmax, rmax, tmax;

    public Node(int l, int r, int sum, int lmax, int rmax, int tmax) {
        this.l = l;
        this.r = r;
        this.sum = sum;
        this.lmax = lmax;
        this.rmax = rmax;
        this.tmax = tmax;
    }
}
