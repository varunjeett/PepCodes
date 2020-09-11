import java.util.HashMap;

public class extra2 {

    public class pair {
        int sum;
        ArrayList<Integer> al;

        pair() {
            this.sum = 0;
            this.al = new ArrayList<Integer>();
        }

        pair(pair obj) {
            this.sum = obj.sum;
            this.al = new ArrayList<Integer>(obj.al);
        }
    }

    public int kthSmallest(int[][] mat, int k) {

        int n = mat.length;
        int m = mat[0].length;
        pair p = new pair();

        for (int i = 0; i < n; i++) {
            p.sum += mat[i][0];
            p.al.add(i * m);
        }

        PriorityQueue<pair> pq = new PriorityQueue<>((pair a, pair b) -> {
            return a.sum - b.sum;
        });

        pq.add(p);

        while (pq.size() != 0 && k-- > 1) {
            pair rvtx = pq.poll();
            
            for (int idx = 0; idx < rvtx.al.size(); idx++) {
                pair addit = new pair(rvtx);
                int point = addit.al.remove(idx);
                int r = point / m;
                int c = point % m;
                addit.sum -= mat[r][c];
                if (c + 1 < m) {
                    addit.sum += mat[r][c + 1];
                    addit.al.add((r * m) + c + 1, idx);
                }
                pq.add(addit);
            }
        }
        return pq.peek().sum;
    }

    public static void solve() {

        String s = "aabbtbcdabt";
        String t = "at";
        System.out.println(minWindow(s, t));

    }

    public static void main(String[] args) {
        solve();
    }

}