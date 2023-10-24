import java.io.*;

public class J1117 {
    static int N = 25, res, n;
    static String[] words = new String[N];
    static int[] cnt = new int[N];
    static int g[][] = new int[N][N]; // g[i][j]表示第i个单词和第j个单词重叠最小值
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(br.readLine());
        for (int i = 0; i < n; i++){
            words[i] = br.readLine();
            cnt[i] = 2;
        }
        char c = br.readLine().charAt(0);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                String a = words[i], b = words[j];
                for (int k = 1; k < Math.min(a.length(), b.length()); k++) 
                    if (a.substring(a.length() - k).equals(b.substring(0, k))) {
                        g[i][j] = k;
                        break;
                    }  
            }

        for (int i = 0; i < n; i++) {
            if (words[i].charAt(0) == c)
                dfs(i, words[i].length());
        }
        System.out.println(res);
    }

    public static void dfs(int x, int len) {
        res = Math.max(res, len);
        cnt[x]--;

        for (int i = 0; i < n; i++) {
            if (g[x][i] > 0 && cnt[i] > 0) {
                dfs(i, len + words[i].length() - g[x][i]);
            }
        }
        cnt[x]++;
    } 
}
