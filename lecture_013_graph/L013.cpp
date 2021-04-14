#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

class Edge
{
public:
  int v;
  int w;

  Edge(int v1, int w1)
  {
    this->v = v1;
    this->w = w1;
  }
};

int N = 8;
vector<vector<Edge *>> graph(N, vector<Edge *>());

void addEdge(int u, int v, int w)
{
  graph[u].push_back(new Edge(v, w));
}

void display()
{

  for (int i = 0; i < N; i++)
  {
    cout << i << "->";
    for (int j = 0; j < graph[i].size(); j++)
    {
      Edge *e = graph[i][j];
      cout << "(" << e->v << "," << e->w << ")";
    }
    cout << endl;
  }
}

void construct()
{

  addEdge(0, 1, 10);
  addEdge(0, 2, 10);
  addEdge(1, 7, 10);
  addEdge(1, 6, 10);
  addEdge(1, 5, 10);
  addEdge(2, 6, 10);
  addEdge(3, 1, 10);
  addEdge(4, 2, 10);
  addEdge(4, 5, 10);
  addEdge(7, 1, 10);
  display();
}

vector<int> topodfs(int src, vector<bool> &vis, vector<int> &ans)
{
  vis[src] = true;

  for (int i = 0; i < graph[src].size(); i++)
  {
    Edge *e = graph[src][i];
    if (!vis[e->v])
      topodfs(e->v, vis, ans);
  }

  ans.push_back(src);
  return ans;
}

void topoSort()
{
  vector<bool> vis(N, false);
  vector<int> ret;
  vector<int> ans;

  for (int i = 0; i < N; i++)
  {
    if (!vis[i])
      ret = topodfs(i, vis, ans);
  }

  //print the ret in reverse
  for (int j = ans.size() - 1; j >= 0; j--)
    cout << ans[j] << ",";

  cout << endl;
}

void kahnalgo()
{
  //creation of indegree
  vector<int> indegree(N, 0);
  queue<int> q;
  vector<int> ans;

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < graph[i].size(); j++)
      ++indegree[graph[i][j]->v];
  }

  for (int i = 0; i < N; i++)
  {
    if (indegree[i] == 0)
      q.push(i);
  }

  while (q.size() != 0)
  {
    int rvtx = q.front();
    q.pop();

    for (int i = 0; i < graph[rvtx].size(); i++)
    {
      Edge *e = graph[rvtx][i];
      indegree[e->v]--;
      if (indegree[e->v] == 0)
        q.push(e->v);
    }

    ans.push_back(rvtx);
  }

  if (ans.size() != N)
    cout << "Cycle" << endl;

  else
  {
    for (int j = 0; j < ans.size(); j++)
      cout << ans[j] << ",";
  }
}

bool cycledetectDFS(int src, vector<int> &vis, unordered_set<int> &ans)
{
  if (vis[src] == 1)
    return true;

  if (vis[src] == 2)
    return false;

  vis[src] = 1;
  bool res = false;

  for (int i = 0; i < graph[src].size(); i++)
  {
    res = res || cycledetectDFS(graph[src][i]->v, vis, ans);
  }

  vis[src] = 2;

  if (res)
    ans.insert(src);

  return res;
}

void cycledetect()
{
  vector<int> vis(N, -1);
  bool res = false;
  unordered_set<int> ans;
  for (int i = 0; i < N; i++)
  {
    if (vis[i] == -1)
      res = res || cycledetectDFS(i, vis, ans);
  }

  if (res)
    cout << "CYCLE \n";
  else
  {
    cout << "NO CYCLE \n";
    for (int i = ans.size() - 1; i >= 0; i--)
      cout << ans[i] << ",";
  }
}

void solve()
{

  construct();
  //topoSort();
  //kahnalgo();
  cycledetect();
}

int main()
{
  solve();
}


