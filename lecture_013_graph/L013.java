import java.util.ArrayList;
import java.util.LinkedList;

public class L013 {
    public static void main(String[] args) {
        solve();
    }

    public static void display(ArrayList<Integer>[] graph) {

        for (int i = 0; i < graph.length; i++) {
            System.out.print(i + "-> "); // u

            for (Integer e : graph[i]) {
                System.out.print(e + ", "); // v
            }
            System.out.println();
        }

        System.out.println();
    }

    public static void constructGraph(ArrayList<Integer>[] graph) {

        for (int i = 0; i < graph.length; i++) {
            graph[i] = new ArrayList<Integer>();
        }

        graph[7].add(4);
        graph[5].add(6);
        graph[5].add(0);
        // graph[0].add(5);

        graph[6].add(7);
        graph[7].add(6);
        graph[3].add(4);
        graph[2].add(3);
        graph[1].add(2);
        graph[1].add(0);

    }

    // topic.===============================================

    public static void solve() {
        int N = 8;
        ArrayList<Integer>[] graph = new ArrayList[N];
        ;
        constructGraph(graph);
        display(graph);
        dfs_improve(graph);
    }

    public static void topo_Sort(ArrayList<Integer>[] graph) {

        boolean[] vis = new boolean[graph.length];
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 0; i < vis.length; i++) {
            if (!vis[i]) {
                topo_dfs(i, graph, vis, ans);
            }
        }

        for (Integer ele : ans) {
            System.out.println(ele);
        }

    }

    public static void topo_dfs(int src, ArrayList<Integer>[] graph, boolean[] vis, ArrayList<Integer> ans) {

        vis[src] = true;
        for (int ele : graph[src]) {
            if (!vis[ele]) {
                topo_dfs(ele, graph, vis, ans);
            }
        }

        ans.add(src);

    }

    public static void Kahn(ArrayList<Integer>[] graph) {

        int[] indegree = new int[graph.length];
        for (int i = 0; i < graph.length; i++) {
            for (int j = 0; j < graph[i].size(); j++)
                indegree[graph[i].get(j)]++;
        }

        LinkedList<Integer> q = new LinkedList<>();
        for (int i = 0; i < indegree.length; i++) {
            if (indegree[i] == 0)
                q.addLast(i);
        }

    }

    public static boolean dfs(int src, ArrayList<Integer>[] graph, boolean[] vis, boolean[] myPath) {

        if (vis[src]) {
            if (myPath[src])
                return true; // as in true for cycle exits
            return false;
        }

        vis[src] = myPath[src] = true;

        boolean res = false;

        for (int ele : graph[src]) {
            res = res || dfs(ele, graph, vis, myPath);
        }

        myPath[src] = false;
        return res;
    }

    public static void dfs_improve(ArrayList<Integer>[] graph) {

        int N = graph.length;
        boolean[] vis = new boolean[N];
        boolean[] myPath = new boolean[N];

        boolean res = false;
        for (int i = 0; i < graph.length; i++) {
            res = res || (dfs(i, graph, vis, myPath));
        }

        System.out.println(res);

    }

}