//SCC 
#include <iostream>
#include <vector>

using namespace std;

class Edge {
  public:

  int v;
  int w;

  Edge(int v1, int w1) {
    this -> v = v1;
    this -> w = w1;
  }

};


int N = 12;

vector < vector < Edge * > > graph (N, vector < Edge * > () );

void addEdge(int u, int v, int w) {

  graph[u].push_back(new Edge(v, w));

}


void display() {

  for (int i = 0; i < N; i++) {
    cout << i << "->";
    for (int j = 0; j < graph[i].size(); j++) {
      Edge * e = graph[i][j];
      cout << "(" << e -> v << "," << e -> w << ")";

    }
    cout << endl;
  }

}

void construct() {
  addEdge(0, 1, 10);
  addEdge(1, 2, 10);
  addEdge(2, 3, 10);
  addEdge(3, 0, 10);
  addEdge(3, 4, 10);
  addEdge(4, 5, 10);
  addEdge(5, 6, 10);
  addEdge(6, 7, 10);
  addEdge(7, 4, 10);
  addEdge(7, 8, 10);
  addEdge(8, 9, 10);
  addEdge(9, 10, 10);
  addEdge(10, 8, 10);
  addEdge(11, 10, 10);

  display();

}
 
vector < int > dfs(vector < int > & order, vector<bool> & vis, int src, vector < vector < Edge *> > & gp)
{   

    vis[src]=true;
    
    for(int i=0;i<gp[src].size();i++)
    {  
        Edge * e = gp[src][i];
        if( vis[ e->v ] == false)
        {
            order = dfs(order,vis,e->v,gp);
        }
    
    }
    
    order.push_back(src);

    return order;

}

int scc() {
   
    //call dfs 
    vector < int > order;
    vector < bool > vis(N,false);

    for(int i=0;i<N;i++)
    {
        if(vis[i]==false)
        {
            order = dfs(order,vis,i,graph);
        }
    }

     //invert the graph
    
    vector < vector < Edge * > > graph2 (N,vector < Edge * >() );
   
    for(int i=0;i<N;i++)
    {
        for(Edge * e : graph[i])
        {  
           // i se  e->v ko change krdo e->v se i mein
           graph2[e->v].push_back(new Edge(i,10));
        }
    }
    

    //call dfs and maintain the count 
    int count=0;

    vector < bool > vis2(N,false);
    
    for(int i = order.size()-1;i>=0;i--)
    { 
      vector <int >  order2;
      
      if( vis2[order[i]]==false )
       {
        ++count;
        order2 = dfs(order2,vis2,order[i],graph2);
          
           for(int ele:order2)
           {
           cout<<ele<<",";
           }
           cout<<endl;
       }

    }
    
    return count;
    
}

void solve() {

  construct();
  cout<<scc();

}

int main() {
  
  solve();

}