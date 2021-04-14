#include <iostream>
#include <vector>
#include <queue>

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

int N = 12;
vector<vector<Edge *>> graph(N, vector<Edge *>());

void addEdge(int u, int v, int w)
{
  graph[u].push_back(new Edge(v, w));
  graph[v].push_back(new Edge(u, w));
}

void constructGraph()
{

  addEdge(0, 1, 10);
  addEdge(0, 3, 10);
  addEdge(1, 2, 10);
  addEdge(2, 3, 40);
  addEdge(3, 4, 2);
  addEdge(4, 5, 2);
  addEdge(4, 6, 3);
  //addEdge(5,6,18);
  addEdge(2, 7, 2);
  addEdge(2, 8, 2);
  //addEdge(7, 8, 12);
  addEdge(9, 10, 5);
  addEdge(9, 11, 8);
}

void display(vector<vector<Edge *>> gp)
{

  for (int i = 0; i < gp.size(); i++)
  {
    cout << i << " -> ";

    for (int j = 0; j < gp[i].size(); j++)
    { //gp[i][j] is basically an object of edge

      cout << "(" << gp[i][j]->v << "," << gp[i][j]->w << ")";
    }

    cout << endl;
  }
}

void bfs01(int src, int desti, vector<bool> &vis)
{
  queue<pair<int, string>> q;
  q.push({src, to_string(src)});
  int cycle = 0;

  while (q.size() != 0)
  {
    pair<int, string> rvtx = q.front();
    q.pop();

    if (vis[rvtx.first])
    {
      cout << "cycle: " << rvtx.second << endl;
      cycle++;
      continue;
    }

    vis[rvtx.first] = true; //queue se nikalne ke baad hi true mark hoga

    if (rvtx.first == desti)
    {
      cout << "desti: " << rvtx.second << endl;
    }

    for (Edge *e : graph[rvtx.first])
    {
      if (!vis[e->v])
        q.push({e->v, rvtx.second + to_string(e->v)});
    }
  }

  cout << "No of cycle: " << cycle << endl;
}

void bfs02(int src, int desti, vector<bool> &vis)
{

  queue<int> q;
  q.push(src);
  int level = 0;
  int cycle = 0;
  int curSize = 0;

  while (q.size() != 0)
  {
    curSize = q.size();

    while (curSize-- > 0)
    {
      int rvtx = q.front();
      q.pop();

      if (vis[rvtx])
      {
        cout << "cycle no: " << cycle << "at " << rvtx << endl;
        cycle++;
        continue;
      }

      vis[rvtx] = true;

      if (rvtx == desti)
        cout << "desti: " << level << endl;

      for (Edge *e : graph[rvtx])
      {
        if (!vis[e->v])
          q.push(e->v);
      }
    }
    level++;
  }
}

void bfs03(int src, int desti, vector<bool> &vis)
{
  //mark true as soon as you put it in the queue, 
  queue<int> q;
  q.push(src);
  int level = 0;
  vis[src] = true;

  int curSize = 0;

  while (q.size() != 0)
  {
    curSize = q.size();

    while (curSize-- > 0)
    {
      int rvtx = q.front();
      q.pop();

      if (rvtx == desti)
        cout << "desti: " << level << endl;

      for (Edge *e : graph[rvtx])
      {
        if (!vis[e->v])
        {
          q.push(e->v);
          vis[e->v] = true;
        }
      }
    }
    level++;
  }
}

void bfsSet()
{
  vector<bool> vis(N, false);
  int src = 0;
  int desti = 6;
  // bfs01(src,desti,vis);
  bfs02(src, desti, vis);
  //bfs03(src,desti,vis);  //cycle detection is not the motive
}

int lc1091(vector<vector<int>> &grid)
{
  if (grid.size() == 0 || grid[0].size() == 0)
    return 0;

  int n = grid.size();

  if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
    return -1;

  queue<int> q;
  q.push(0);
  grid[0][0] = 1; //source ko true mark krdia
  int curSize = 0;
  int level = 1;

  vector<vector<int>> dir = {{1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, -1}, {0, 1}, {-1, 1}, {1, -1}};

  while (q.size() != 0)
  {
    curSize = q.size();

    while (curSize-- > 0)
    {
      int vtx = q.front();
      q.pop();

      int r = vtx / n;
      int c = vtx % n;

      if (r == n - 1 && c == n - 1)
      {
        return level;
      }

      for (int d = 0; d < 8; d++)
      {
        int x = r + dir[d][0];
        int y = c + dir[d][1];
        if (x >= 0 && y >= 0 && x < n && y < n && grid[x][y] == 0)
        {
          q.push(x * n + y);
          grid[x][y] = 1; //true mark krdia
        }
      }
    }
    level++;
  }
  return -1;
}


vector<vector<int>> rooms = {{2147483647, -1, 0, 2147483647}, {2147483647, 2147483647, 2147483647, -1}, {2147483647, -1, 2147483647, -1}, {0, -1, 2147483647, 2147483647}};
void lc285(vector<vector<int>> &rooms)
{

  if (rooms.size() == 0 || rooms[0].size() == 0)
    return;

  int n = rooms.size();
  int m = rooms[0].size();

  vector<vector<int>> dirA = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

  queue<int> q;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (rooms[i][j] == 0)
        q.push(i * m + j);
    }
  }

  int level = 1;
  int cursize = 0;
  int x = 0;
  int y = 0;
  int r = 0;
  int c = 0;

  while (q.size() != 0)
  {
    cursize = q.size();

    while (cursize-- > 0)
    {

      int rvtx = q.front();
      q.pop();

      r = rvtx / m;
      c = rvtx % m;

      for (int d = 0; d < 4; d++)
      {
        x = r + dirA[d][0];
        y = c + dirA[d][1];

        if (x >= 0 && y >= 0 && x < n && y < m && rooms[x][y] == 2147483647)
        {
          q.push(x * m + y);
          rooms[x][y] = level; //true mark krdia
        }
      }
    }
    level++;
  }
}

void lc()
{

  vector<vector<int>> grid = {{0, 0, 1, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 1}, {0, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 1, 1, 1, 0}, {1, 0, 0, 1, 1, 0, 0}, {1, 1, 1, 1, 1, 0, 1}, {0, 0, 1, 0, 0, 0, 0}};
  //cout<<lc1091(grid)<<endl;

  lc285(rooms);

  for (int i = 0; i < rooms.size(); i++)
  {
    for (int j = 0; j < rooms[0].size(); j++)
    {
      cout << rooms[i][j] << " ";
    }
    cout << endl;
  }
}

bool bipartiteBFS(int src, vector<int> &vis)
{

  queue<pair<int, int>> q;

  q.push({src, 0});

  int cursize = 0;

  while (q.size() != 0)
  {

    cursize = q.size();

    while (cursize-- > 0)
    {
      pair<int, int> vtx = q.front();
      q.pop();

      if (vis[vtx.first] != -1)
      {
        if (vtx.second != vis[vtx.first])
          return true;
        else
          continue;
      }

      vis[vtx.first] = vtx.second;

      for (int i = 0; i < graph[vtx.first].size(); i++)
      {
        Edge *e = graph[vtx.first][i];
        if (vis[e->v] == -1)// wherever cycle is present, one of the node automatically gets  in the queue twice
        {
          q.push({e->v, (vtx.second + 1) % 2});
        }
      }
    }
  }
  return false;
}

void bipartite()
{

  vector<int> vis(N, -1);
  bool res = false;

  for (int i = 0; i < N && (!res); i++)
  {
    if (vis[i] == -1) //unvisited
    {
      res = res || bipartiteBFS(i, vis); //call bfs for this
    }
  }
  if (res)
    cout << "its not bipartite\n";
  else
    cout << "its bipartite\n";

  return;
}

void solve()
{
  constructGraph();
  display(graph);
  bfsSet();
  // lc();
  // bipartite();
}

int main()
{
  solve();
}