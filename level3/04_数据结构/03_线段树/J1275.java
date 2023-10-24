import java.io.*;

public class J1275 {
    static final int N = 200010;
    static Node[] tr = new Node[4 * N];
    static int m, p;

    static void build(int u, int l, int r) {
        tr[u] = new Node(l, r);
        if (l == r)
            return;
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }

    // 由子节点计算父节点
    static void pushup(int u) {
        tr[u].v = Math.max(tr[u << 1].v, tr[u << 1 | 1].v);
    }

    static int query(int u, int l, int r){
        if (tr[u].l >= l && tr[u].r <= r)
            return tr[u].v;
        int mid = tr[u].l + tr[u].r >> 1;
        int v = 0;
        if (l <= mid) v = query(u << 1, l, r);
        if (r > mid) v = Math.max(v, query(u << 1 | 1, l, r));
        return v;
    }

    // 将第x个点的修改为y
    static void modify(int u, int x, int y) {
        if (tr[u].l == x && tr[u].r == x) {
            tr[u].v = y;
            return;
        }
            
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid)
            modify(u << 1, x, y);
        else
            modify(u << 1 | 1, x, y);
        pushup(u);
    }


    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        m = Integer.parseInt(str[0]);
        p = Integer.parseInt(str[1]);
        
        build(1, 1, m);

        int last = 0;
        int n = 0; // n表示当前已有的节点数
        for (int i = 0; i < m; i++) {
            str = br.readLine().split(" ");
            if ("Q".equals(str[0])) {
                int l = Integer.parseInt(str[1]);
                last = query(1, n - l + 1, n);
                System.out.println(last);
            } else {
                int t = Integer.parseInt(str[1]);
                modify(1, n + 1, (int)(((long)t + last) % p));
                n++;
            }
        }
    }
}

class Node {
    int l, r;
    int v; // 区间[l,r]最大值
    public Node(int l, int r){
        this.l = l;
        this.r = r;
    }
}
