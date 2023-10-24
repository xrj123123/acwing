/*
    类floyd + 快速幂
    题目需要求出从s到e经过k条边的最短距离
    floyd算法是通过dp转化而来，f[k,i,j]表示只经过1-k之间的点，i到j之间的最短路径。那么我们改变一下，让f[k,i,j]表示从i到j只经过k条边的最短路径
    f[a+b,i,j] = min(f[a+b,i,j], f[a,i,k] + f[b,k,j])  从i到j经过a+b条边的最短路等于从i到k经过a条边的最短路加上从k到j经过b条边的最短路
    因此我们可以求出经过1条边所有点之间的最短路，2条边、3条边...n条边，最终答案就是f[n,s,e], 因此需要做n次floyd，时间复杂度为O(N*n^3)，N是经过边的数量

    s、x1、x2、...k、...xn-1、e，我们最终求得是f[n,s,e]，其中求f[n1,s,k]和f[n2,k,e]是互不影响的，分别求出其最小值，然后就可以求出f[n1+n2,s,e]
    即存在结合律，那么我们就可以使用快速幂来做，就是通过倍增的思想来优化。
    先求出经过1条边的最短路，然后求出经过2条边的，然后就可以求出经过4条边的最短路，后边以此类推，和快速幂是一样的了，时间复杂度为O(logN*n^3)

    由于最多100条边即最多200个点，而点的范围是1000，我们需要先对点做一个离散化
*/
import java.io.*;
import java.util.*;

public class J345 {
    static int N = 210;
    static int k, n, m, s, e;
    static int[][] g = new int[N][N], res = new int[N][N];
    static Map<Integer, Integer> idx = new HashMap<>();

    static void mul(int[][] c, int[][] a, int[][] b){
        /*
            c表示a*b的结果, 需要用一个临时变量t来表示结果，然后在赋值给c
            因为数组a表示经过n1条边，数组b表示经过n2条边，我们最终求的是经过n1+n2条边，但是现在数组c是经过n1条边的，最终需要将c变为n1+n2条边
            如果数组c，从i到j经过n1条边比，经过a和b计算从i到j经过n1+n2条边的距离小, c是不会被更新的，所以需要开一个临时数组
        */ 
        int[][] t = new int[N][N];
        for (int i = 0; i < N; i++)
            Arrays.fill(t[i], 0x3f3f3f3f);

        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    t[i][j] = Math.min(t[i][j], a[i][k] + b[k][j]);

        for (int i = 0; i < N; i++)
            c[i] = Arrays.copyOf(t[i], t[i].length);
    }

    static void qmi(){
        // 初始时res[i][j]表示从i到j经过0条边的最短路
        for (int i = 0; i < N; i++){
            Arrays.fill(res[i], 0x3f3f3f3f);
            res[i][i] = 0;
        }

        while (k > 0) {
            if ((k & 1) == 1) 
                mul(res, res, g);   // res = res * g  
            mul(g, g, g);   // g = g * g
            k >>= 1;
        }
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] str = br.readLine().split(" ");
        k = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
        s = Integer.parseInt(str[2]);
        e = Integer.parseInt(str[3]);

        if (!idx.containsKey(s)) idx.put(s, n++);
        if (!idx.containsKey(e)) idx.put(e, n++);
        s = idx.get(s);
        e = idx.get(e);

        // g[i][j]表示从i到j经过1条边的最短路
        for (int i = 0; i < N; i++)
            Arrays.fill(g[i], 0x3f3f3f3f);

        while (m-- > 0) {
            str = br.readLine().split(" ");
            int a = Integer.parseInt(str[1]);
            int b = Integer.parseInt(str[2]);
            int c = Integer.parseInt(str[0]);
            if (!idx.containsKey(a)) idx.put(a, n++);
            if (!idx.containsKey(b)) idx.put(b, n++);
            a = idx.get(a);
            b = idx.get(b);
            g[a][b] = g[b][a] = Math.min(g[a][b], c);
        }

        qmi();
        System.out.println(res[s][e]);
    }    
}
