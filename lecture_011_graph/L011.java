import java.util.ArrayList;

public class L011 {

    public static class edge {
        int v = 0; // destination
        int w = 0; // weight

        edge(int v, int w) {
            this.v = v;
            this.w = w;
        }
    }

    public static void constructGraph(ArrayList<edge>[] graph) {

        int N = graph.length;
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<edge>(); // allocate memory to each array value
        }

        addEdge(graph, 0, 1, 10);
        addEdge(graph, 0, 3, 10);
        addEdge(graph, 1, 2, 10);
        addEdge(graph, 2, 3, 10);
        //   addEdge(graph, 3, 4, 10); // for dfs
        
        addEdge(graph, 7, 11, 10); 
        addEdge(graph, 10, 11, 10); 
        addEdge(graph, 9, 11, 10); 
        addEdge(graph, 8, 11, 10); 

        addEdge(graph, 12, 13, 10); 

        addEdge(graph, 4, 5, 10);
        addEdge(graph, 4, 6, 10);
        addEdge(graph, 5, 6, 10);

    }

    public static void addEdge(ArrayList<edge>[] graph, int u1, int v1, int w1) {

        // bi-directional graph
        graph[u1].add(new edge(v1, w1));
        graph[v1].add(new edge(u1, w1));
    }

    public static void display(ArrayList<edge>[] graph) {

        int N = graph.length;
        for (int i = 0; i < N; i++) {
            System.out.println();
            System.out.print(i + "->");
            for (edge e : graph[i])
                System.out.print("(" + e.v + "," + e.w + ")");

        }

        System.out.println();

    }

    public static int findEdge(ArrayList<edge>[] graph, int u, int v) { // u ke andar v

        for (int i = 0; i < graph[u].size(); i++) {
            edge e = graph[u].get(i);
            if (e.v == v)
                return i;
        }

        return -1;
    }

    public static void removeEdge(ArrayList<edge>[] graph, int u, int v) { // u ke andar v

        int idx1 = findEdge(graph, u, v);
        if (idx1 != -1)
            graph[u].remove(idx1);

        int idx2 = findEdge(graph, v, u);
        if (idx2 != -1)
            graph[v].remove(idx2);

    }

    public static void removeVtx(ArrayList<edge>[] graph, int vtx) {

        while (graph[vtx].size() != 0) {
            edge e = graph[vtx].get(graph[vtx].size() - 1);
            removeEdge(graph, vtx, e.v);
        }
    }

    public static int hamil_path(ArrayList<edge>[] graph, int src, int N, boolean[] vis, String ans, int osrc) {

        if (N == graph.length - 1) {
            System.out.println("Path:" + ans + src);
            if (findEdge(graph, src, osrc) != -1)
                System.out.println("Cycle:" + ans + src + "->" + osrc);

            return 1;
        }

        vis[src] = true;

        int count = 0;
        for (edge e : graph[src]) {
            if (!vis[e.v]) {
                count += hamil_path(graph, e.v, N + 1, vis, ans + src + "->", osrc);
            }
        }

        vis[src] = false;
        return count;

    }

    public static void GCC_dfs(ArrayList<edge>[] graph, int src, boolean[] vis) {
        
        vis[src] = true;
        for (edge e : graph[src]) {
            if (!vis[e.v]) {
                GCC_dfs(graph, e.v, vis);
            }
        }
        return ;
    }

    public static int GCC(ArrayList<edge>[] graph, boolean[] vis) {

        int count = 0;
        for (int i = 0; i < vis.length; i++){
            if (!vis[i]) {
                GCC_dfs(graph, i, vis);
                count++;
            }
        }

        return count;
    }

    public static void question(ArrayList<edge>[] graph) {
        // int src = 0;
        // boolean[] vis = new boolean[graph.length];
        // System.out.println(hamil_path(graph, src, 0, vis, "", 0));

        boolean[] vis2 = new boolean[graph.length];
        System.out.println(GCC(graph, vis2));

    }

    public static void solve() {

        int N = 14; // no of vertices
        // float [] f = new float[N];
        ArrayList<edge>[] graph = new ArrayList[N];

        constructGraph(graph);
        display(graph);

        question(graph);

    }

    public static void main(String[] args) {
        solve();
    }

}