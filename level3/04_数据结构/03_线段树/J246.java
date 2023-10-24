import java.io.*;

class J246 {
    static final int N = 500010;
    static long[] a = new long[N];
    static Node[] tr = new Node[4 * N];
    static int n, m;

    static long gcd(long a, long b) {
        return b == 0 ? Math.abs(a) : gcd(b, a % b);
    }

    static void build(int u, int l, int r) {
        if (l == r) {
            tr[u] = new Node(l, r, a[l] - a[l - 1], a[l] - a[l - 1]);
        } else {
            int mid = l + r >> 1;
            tr[u] = new Node(l, r);
            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);
            pushup(u);
        }
    }

    static void pushup(int u) {
        pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
    }

    static void pushup(Node u, Node l, Node r) {
        u.sum = l.sum + r.sum;
        u.d = gcd(l.d, r.d);
    }

    static void modify(int u, int x, long v) {
        if (tr[u].l == x && tr[u].r == x) {
            tr[u].sum += v;
            tr[u].d += v;
        } else {
            int mid = tr[u].l + tr[u].r >> 1;
            if (x <= mid)
                modify(u << 1, x, v);
            else
                modify(u << 1 | 1, x, v);
            pushup(u);
        }
    }

    static Node query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r)
            return tr[u];
        
        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid) return query(u << 1, l, r);
        if (l > mid) return query(u << 1 | 1, l, r);
        
        Node res = new Node(0, 0);
        Node left = query(u << 1, l, r);
        Node right = query(u << 1 | 1, l, r);
        pushup(res, left, right);

        return res;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);

        str = br.readLine().split(" ");
        for (int i = 1; i <= n; i++) {
            a[i] = Long.parseLong(str[i - 1]);
        }

        build(1, 1, n);

        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            char op = str[0].charAt(0);
            int l = Integer.parseInt(str[1]);
            int r = Integer.parseInt(str[2]);

            if (op == 'C') {
                long d = Long.parseLong(str[3]);
                modify(1, l, d);
                if (r + 1 <= n) modify(1, r + 1, -d);
            } else {
                Node left = query(1, 1, l);
                Node right = new Node(0, 0);
                if (l + 1 <= r) right = query(1, l + 1, r);
                System.out.println(gcd(left.sum, right.d));
            }
        }
    }
}

class Node {
    int l, r;
    long sum, d;  // sum表示前缀和，d表示区间l到r的最大公约数
    public Node(int l, int r) {
        this.l = l;
        this.r = r;
    }
    public Node(int l, int r, long sum, long d) {
        this.l = l;
        this.r = l;
        this.sum = sum;
        this.d = d;
    }
}
