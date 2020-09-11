public class question {

    // without duplicates, the first path will give us the answer.
    class Solution {
        public int swimInWater(int[][] arr) {
            int n = arr.length;
            int m = arr[0].length;

            boolean[][] vis = new boolean[n][m];
            PriorityQueue<int[]> pq = new PriorityQueue<>((int[] a, int[] b) -> {
                return arr[a[1] / m][a[1] % m] - arr[b[1] / m][b[1] % m];
            });

            pq.add(new int[] { 0, 0 }); // (time,pos)
            vis[0][0] = true;

            int[] dir = new int[] { -1, 0, 1, 0, -1 };

            while (pq.size() != 0) {
                int[] rvtx = pq.poll();

                int time = rvtx[0];
                int r = rvtx[1] / m;
                int c = rvtx[1] % m;

                if (r == n - 1 && c == m - 1) {
                    return time; // no need to check minimum in this case.
                }

                for (int d = 0; d < dir.length - 1; d++) {
                    int x = r + dir[d];
                    int y = c + dir[d + 1];

                    if (x >= 0 && y >= 0 && x < n && y < m && !vis[x][y]) {
                        vis[x][y] = true;
                        pq.add(new int[] { Math.max(time, (Math.max(arr[r][c], arr[x][y]))), x * m + y });
                    }

                }
            }

            return -1;
        }
    }

    // trapping rain water, with duplicates allowed.
    class Solution {
        public int swimInWater(int[][] arr) {
            int n = arr.length;
            int m = arr[0].length;

            boolean[][] vis = new boolean[n][m];
            PriorityQueue<int[]> pq = new PriorityQueue<>((int[] a, int[] b) -> {
                return arr[a[1] / m][a[1] % m] - arr[b[1] / m][b[1] % m];
            });

            pq.add(new int[] { 0, 0 }); // (time,pos)
            vis[0][0] = true;

            int ans = 10000000;

            int[] dir = new int[] { -1, 0, 1, 0, -1 };

            while (pq.size() != 0) {
                int[] rvtx = pq.poll();

                int time = rvtx[0];
                int r = rvtx[1] / m;
                int c = rvtx[1] % m;

                vis[r][c] = true;

                if (r == n - 1 && c == m - 1) {
                    ans = Math.min(ans, time); // we are exploring all the paths
                }

                for (int d = 0; d < dir.length - 1; d++) {
                    int x = r + dir[d];
                    int y = c + dir[d + 1];

                    if (x >= 0 && y >= 0 && x < n && y < m && !vis[x][y]) {
                        pq.add(new int[] { Math.max(time, (Math.max(arr[r][c], arr[x][y]))), x * m + y });
                    }

                }
            }

            return ans;
        }
    }

    // leetcode 1439.=======================================
    class Solution {
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
            HashSet<ArrayList<Integer>> map = new HashSet<>();

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

                    int point = rvtx.al.get(idx);
                    int r = point / m;
                    int c = point % m;

                    if (c + 1 < m) {
                        pair addit = new pair(rvtx);
                        addit.sum -= mat[r][c];
                        addit.sum += mat[r][c + 1];
                        addit.al.set(idx, (r * m) + c + 1);

                        if (!map.contains(addit.al)) {
                            pq.add(addit);
                            map.add(addit.al);
                        }

                    }
                }
            }
            return pq.peek().sum;
        }

    }
}
