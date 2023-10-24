import java.io.*;

public class J1123 {
    
    static double getDist(double x1, double y1, double x2, double y2) {
        double t = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
        return Math.sqrt(t);
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        double sum = 0;
        
        String[] str = br.readLine().split(" ");
        int x = Integer.parseInt(str[0]), y = Integer.parseInt(str[1]);
        
        String data = "";
        while ((data = br.readLine()) != null) {
            str = data.split(" ");
            double x1 = Double.parseDouble(str[0]);
            double y1 = Double.parseDouble(str[1]);
            double x2 = Double.parseDouble(str[2]);
            double y2 = Double.parseDouble(str[3]);
            sum += getDist(x1, y1, x2, y2);
        }
        
        sum *= 2;
        sum /= 1000; // km
        int h = (int)(sum / 20); // 小时
        int m = (int)((sum - 20 * h) * 3 + 0.5); // 分钟
        
        System.out.print(h + ":");
        if (m < 10)
            System.out.print(0);
        System.out.println(m);
    }
}