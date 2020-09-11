import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

public class extra {
    public static void main(String[] args) {
        // int[][] board = { { -1, -1, -1, -1, -1, -1 }, { -1, -1, -1, -1, -1, -1 }, {
        // -1, -1, -1, -1, -1, -1 },
        // { -1, 35, -1, -1, 13, -1 }, { -1, -1, -1, -1, -1, -1 }, { -1, 15, -1, -1, -1,
        // -1 } };

        // System.out.println(snakesAndLadders(board));

        // int[] val = { 5, 4, 3, 2, 1 };
        // int[] lab = { 1, 1, 2, 2, 3 };
        // System.out.println(largestValsFromLabels(val, lab, 3, 1));
        // List<String> ans=new ArrayList<>();
        // ans.add("abc");
        // ans.add("def");
        // System.out.println(ans);
        // System.out.println(findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"));
        int[] arr1 = { 1, 2, 4 };
        int[][] arr = { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 }, { 9, 10 } };
        Arrays.sort(arr, (int[] a, int[] b) -> {
            return a[0] - b[0];
        });
        System.out.println(arr[4][1]);
    }

    public static class die {

        int pos;
        int turn;

        die(int p, int t) {
            this.pos = p;
            this.turn = t;
        }

    }

    public static int snakesAndLadders(int[][] arr) {

        int n = arr.length;
        int m = arr[0].length;

        int[] newboard = new int[n * m + 1];

        int count = 0;

        boolean lefttoright = true;

        for (int i = n - 1; i >= 0; i--) {

            if (lefttoright) {

                for (int j = 0; j < m; j++) {
                    newboard[count++] = arr[i][j];
                }

            }

            else {
                for (int j = m - 1; j >= 0; j--) {
                    newboard[count++] = arr[i][j];
                }
            }

            lefttoright = !lefttoright;
        }

        for (int i = 0; i < newboard.length - 1; i++) {

            int x = i / m;
            int y = i % m;

            arr[x][y] = newboard[i];
            newboard[i] = 0;
        }

        // vis is newboard
        LinkedList<die> q = new LinkedList<>();

        die src = new die(1, 0);

        if (arr[0][0] != -1) {
            src.pos = arr[0][0];
        }

        q.addLast(src);
        newboard[1] = 1;

        while (q.size() != 0) {

            die rvtx = q.removeFirst();

            if (rvtx.pos == (n * m)) {
                return rvtx.turn;
            }

            for (int roll = 1; roll <= 6; roll++) {

                int idx = rvtx.pos + roll;

                if (idx <= n * m) {

                    int x = idx / m;
                    int y = idx % m;

                    int ele = arr[x][y];

                    if (ele != -1) {
                        if (newboard[ele] == 0) {
                            newboard[ele] = 1;
                            q.addLast(new die(ele, rvtx.turn + 1));
                        }
                    } else {
                        if (newboard[idx] == 0) {
                            newboard[idx] = 1;
                            q.addLast(new die(idx, rvtx.turn + 1));
                        }
                    }

                }
            }

        }
        return -1;
    }

    public static int largestValsFromLabels(int[] values, int[] labels, int num_wanted, int use_limit) {

        int len = labels.length;
        PriorityQueue<int[]> pq = new PriorityQueue<int[]>((int[] a, int[] b) -> b[0] - a[0]);
        for (int i = 0; i < len; i++) {
            int[] arr = { values[i], labels[i] };
            pq.add(arr);
        }

        HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
        int sum = 0;

        while (num_wanted > 0) {

            int[] rvtx = pq.peek();
            pq.poll();
            int val = map.getOrDefault(rvtx[1], 0);
            val++; // including current
            map.put(rvtx[1], val); // updating in map

            if (val <= use_limit) {
                num_wanted--;
                sum += rvtx[0];
            }

        }

        return sum;
    }

    public static List<String> findRepeatedDnaSequences(String s) {
        List<String> ll = new ArrayList<String>();
        int i = 0;
        HashMap<String, Integer> map = new HashMap<String, Integer>();
        while (i + 10 <= s.length()) {
            String str = s.substring(i, i + 10);
            i++;
            int val = map.getOrDefault(str, 0);
            if (val == 1)
                ll.add(str); // repeating for the first time ; add in the list as we dont want to add it more
                             // than once
            map.put(str, val + 1);

        }
        return ll;
    }

}

