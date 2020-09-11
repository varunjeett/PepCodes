import java.util.ArrayList;

public class L010 {

    public static class edge {
        int v = 0; // destination
        int w = 0; // weight

        edge(int v, int w) {
            this.v = v;
            this.w = w;
        }
    }

    public static void main(String[] args) {
        solve();
    }

    public static void solve() {

        int N = 7; // no of vertices
        // float [] f = new float[N];
        ArrayList<edge>[] graph = new ArrayList[N];

        constructGraph(graph);
        display(graph);

        // type.===============
        // basic(graph);

        path(graph);
 
    }

    public static void basic(ArrayList<edge>[] graph) {

        removeEdge(graph, 5, 6);
        display(graph);
        addEdge(graph, 5, 6, 10);
        display(graph);
        removeVtx(graph, 3);
        display(graph);

    }

    public static void path(ArrayList<edge>[] graph) {

        boolean[] vis = new boolean[graph.length];
        // System.out.println(hasPath(graph, 2, 6, vis));
        // System.out.println(allPath(graph, 0, 6, vis, "", 0));
        pair_ ans=allPath_pair(graph,0,6,vis);
        System.out.println(ans.cost+" @ "+ans.way);

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
        addEdge(graph, 3, 4, 10);
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

    public static boolean hasPath(ArrayList<edge>[] graph, int src, int des, boolean[] vis) {
        if (src == des)
            return true;

        boolean res = false;
        vis[src] = true;
        for (edge e : graph[src]) {
            if (!vis[e.v])
                res = res || hasPath(graph, e.v, des, vis);
        }
        vis[src] = false;

        return res;
    }

    public static int allPath(ArrayList<edge>[] graph, int src, int des, boolean[] vis, String ans, int w) {
        if (src == des) {
            System.out.println(ans + des + " @ " + w);
            return 1;
        }

        int count = 0;
        vis[src] = true;

        for (edge e : graph[src]) {
            if (!vis[e.v])
                count += allPath(graph, e.v, des, vis, ans + src + "->", w + e.w);
        }

        vis[src] = false;

        return count;
    }

    public static class pair_ {
        int cost = 0;      // destination
        String way = "";   // weight

        pair_(int v, String w) {
            this.cost = v;
            this.way = w;
        }
    }

    //for maximum path 
    public static pair_ allPath_pair(ArrayList<edge>[] graph, int src, int des, boolean[] vis) {
        if (src == des) {
            return new pair_(0,""+des);
        }

        vis[src] = true;
        pair_ p=new pair_(Integer.MIN_VALUE,"");

        for (edge e : graph[src]) {
            if (!vis[e.v])
            {
                pair_ ret=allPath_pair(graph, e.v, des, vis);
                if(ret.cost > p.cost)
                {
                    p.cost=ret.cost+e.w;
                    p.way=ret.way+"<-"+src;
                }
            }
        }

        vis[src] = false;   

        return p;
    }

}