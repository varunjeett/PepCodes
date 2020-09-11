import java.util.ArrayList;

//leetcode 207.===========================
class Solution {
    public boolean dfs(int src, ArrayList<Integer>[] graph, boolean[] vis, boolean[] myPath) {

        if (vis[src]) {
            if (myPath[src])
                return true;         // as in true for cycle exits
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
    
    public boolean canFinish(int numCourses, int[][] pre) {
        
        int N = numCourses;
        ArrayList<Integer>[] graph=new ArrayList[N];
        for(int i=0;i<N;i++) {
            graph[i]=new ArrayList<>();
        }
        
        for(int i=0;i<pre.length;i++) {
            int dependent=pre[i][0];
            int independent=pre[i][1];
            graph[independent].add(dependent);  //edge from independent to dependent
        }
        
        boolean[] vis = new boolean[N];
        boolean[] myPath = new boolean[N];

        boolean res = false;

        for (int i = 0; i < graph.length; i++) 
        {
            res = res || (dfs(i, graph, vis, myPath));  //result becomes true when there is cycle.
        }

        return !res;
    }
}