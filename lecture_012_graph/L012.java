import java.util.ArrayList;
import java.util.LinkedList;

public class L012 {

    public static class Edge {
        int v;
        int w;

        Edge(int v1, int w1) {
            this.v = v1;
            this.w = w1;
        }
    }

    public static void main(String[] args) {
        solve();
    }

    public static int N = 10;
    public static ArrayList<Edge>[] graph;

    public static void solve() {
        constructGraph();
        display();
        bfs();
    }

    public static void constructGraph() {

        graph = new ArrayList[N];

        for (int i = 0; i < N; i++)
            graph[i] = new ArrayList<Edge>();

        addEdge(0, 1, 10);
        addEdge(0, 3, 10);
        addEdge(1, 2, 10);
        addEdge(2, 3, 10);
        addEdge(3, 4, 10);
        addEdge(4, 5, 10);
        addEdge(4, 6, 10);
        addEdge(5, 6, 10);
        addEdge(2, 7, 10);
        addEdge(2, 8, 10);
        addEdge(7, 8, 10);

    }

    public static void display() {

        for (int i = 0; i < N; i++) {
            System.out.print(i + "-> ");

            for (int j = 0; j < graph[i].size(); j++) {
                Edge e = graph[i].get(j);
                System.out.print("(" + e.v + "," + e.w + ")");

            }
            System.out.println();
        }

    }

    public static void addEdge(int u, int v, int w) {
        graph[u].add(new Edge(v, w));
        graph[v].add(new Edge(u, w));
    }

    public static void bfs() {
        int src = 0;
        int desti = 6;
        boolean[] vis = new boolean[N];
        bfs_null(src, desti, vis);

        vis = new boolean[N];
        bfs_level(src, desti, vis);
    }

    public static class pair {
        int vtx;
        String path;
        int level;

        pair(int vtx1, String path1) {
            this.vtx = vtx1;
            this.path = path1;
        }

        pair(int vtx1, String path1, int level1) {
            this.vtx = vtx1;
            this.path = path1;
            this.level = level1;
        }
    }

    public static void bfs_null(int src, int desti, boolean[] vis) {

        int level = 0;
        LinkedList<pair> q = new LinkedList<>();
        q.addLast(new pair(src, src + " "));
        q.addLast(null);

        while (q.size() != 1) {

            pair rvtx = q.removeFirst();

            if (vis[rvtx.vtx]) {
                System.out.println("cycle: " + rvtx.path);
                continue;
            }

            vis[rvtx.vtx] = true;

            if (rvtx.vtx == desti) {
                System.out.println("destination: " + rvtx.path + "level is: " + level);
            }

            for (Edge e : graph[rvtx.vtx]) {
                if (!vis[e.v])
                    q.addLast(new pair(e.v, rvtx.path + e.v + " "));
            }

            if (q.getFirst() == null) {
                ++level;
                q.removeFirst();
                q.addLast(null);
            }

        }
    }

    public static void bfs_level(int src, int desti, boolean[] vis) {

        LinkedList<pair> q = new LinkedList<>();
        q.addLast(new pair(src, src + " ", 0));

        while (q.size() != 0) {
            pair rvtx = q.removeFirst();

            if (vis[rvtx.vtx]) {
                System.out.println("cycle: " + rvtx.path);
                continue;
            }

            vis[rvtx.vtx] = true;

            if (rvtx.vtx == desti) {
                System.out.println("destination: " + rvtx.path + "level is: " + rvtx.level);
            }

            for (Edge e : graph[rvtx.vtx]) {
                if (!vis[e.v])
                    q.addLast(new pair(e.v, rvtx.path + e.v + " ", rvtx.level + 1));
            }

        }
    }
}