#include <iostream>
#include <vector>

using namespace std;

class edge{ 
    public:
    int v;
    int w;

    edge(int v1,int w1)
    {
       this->v=v1;
       this->w=w1;
    }
};

//graph is global here
int V=7;
vector<vector<edge>> graph(V,vector<edge>());

void addEdge(int u,int v,int w){
    graph[u].push_back(edge(v,w));
    graph[v].push_back(edge(u,w));
}

void display(){
  
    for(int i=0;i<graph.size();i++)
    {   cout<<i<<"->";
        for(edge e:graph[i])
        {
          cout<<"("<<e.v<<","<<e.w<<") ";
        }
        cout<<endl;
    }

}

void constructGraph(){
 addEdge(0,1,10);
 addEdge(0,3,10);
 addEdge(1,2,10);
 addEdge(2,3,40);
 addEdge(3,4,100);
 addEdge(2,5,100);
 addEdge(4,5,2);
 addEdge(4,6,3);
 addEdge(5,6,18);
 display();
 cout<<endl;
}

int retPos(int u1,int v1){
   
    int idx=-1;
    for(int i=0;i<graph[u1].size();i++)
    {
        edge e=graph[u1][i];
        if(e.v==v1)
        {
            idx=i;
            break;
        }
    }

    return idx;
}

void removeEdge(int u,int v){

    int idx1=retPos(u,v);      //u mein vnode ki pos
    int idx2=retPos(v,u);        //v mein u ki pos

    graph[u].erase( graph[u].begin() + idx1);
    graph[v].erase( graph[v].begin() + idx2);
    
}

void removeVertex(int vtx){
    while(graph[vtx].size()!=0)
    {
        int sz=graph[vtx].size();
        edge e=graph[vtx][sz-1];
        removeEdge(vtx,e.v);
    }
}

bool hasPath(int src,int dest,vector<bool>& vis,string ans){
   
   if(src==dest)
   {     
        cout<<ans+to_string(src)<<endl;
        return true;
   }
   
   bool res=false;
   
   vis[src]=true;

   for(edge e:graph[src])
   {
       if(!vis[e.v] && (!res))
        {
           res=res||hasPath(e.v,dest,vis,ans+to_string(src)+" ");
        }
   }
   vis[src]=false;
   return res;
}

int allPath(int src,int dest,vector<bool>& vis,string ans){
   
   if(src==dest)
   {     
        cout<<ans+to_string(src)<<endl;
        return 1;
   }

   int count=0;
   
   vis[src]=true;

   for(edge e:graph[src])
   {
       if(!vis[e.v])
        {
           count+=allPath(e.v,dest,vis,ans+to_string(src)+" ");
        }
   }
  
   vis[src]=false;
   return count;
}

void hamiltonion(int src,int osrc,vector <bool> & vis,string ans,int count){  
   
    if(count==V-1){
        cout<<"Path: "<<ans<<src<<endl;
        if(retPos(src,osrc)!=-1){
            cout<<"Cycle: "<<ans<<src<<"->"<<osrc<<endl;
        }
        return;
    }

    vis[src]=true;

    for(int i=0; i < graph[src].size(); i++){
        edge e=graph[src][i];
        if(!vis[e.v]){
            hamiltonion(e.v, osrc, vis, ans+to_string(src)+"->", count+1);
        }
    }
    
    vis[src]=false;
    return;
    
}
int ans=0;
string ans_string="";

void dfs_GCC(int src,vector <bool> & vis, int count, string s){
    if(count > ans){
        ans=count;
        ans_string=s;      
    }

    vis[src]=true;
    
    for(int i=0; i<graph[src].size(); i++){
        edge e=graph[src][i];
        if(!vis[e.v]){
            dfs_GCC(e.v, vis, count+1, s+to_string(e.v)+"->");
        }
    }

    return;
}

void GCC(vector <bool> & vis){
   
    for(int i=0; i<vis.size(); i++){
       if(!vis[i]){
            dfs_GCC(i, vis, 1, to_string(i)+"->");
       }
    }
}

void basic(){
   
    vector<bool> vis(V,false);
    //removeEdge(6,4);
    //removeVertex(1);
    //cout<<hasPath(0,9,vis,"")<<endl;
    cout<<allPath(0,6,vis,"");
}

int islandPerimeter(vector<vector<int>> &board)
{
    int totalOnes = 0;
    int commonRegion = 0;

    int n = board.size();
    int m = board[0].size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] == 1)
            {
                totalOnes++;
                if (j + 1 < m && board[i][j + 1] == 1)
                    commonRegion++;
                if (i + 1 < n && board[i + 1][j] == 1)
                    commonRegion++;
            }
        }
    }
    return (4 * totalOnes - 2 * commonRegion);
}

void solve(){
    
    vector<bool> vis(V,false);
    constructGraph();
    removeVertex(5);
    display();


    // basic();
    // hamiltonion(2,2,vis,"",0);
    
    // GCC(vis);
    // cout<<ans<<" , "<<ans_string<<endl;

}


int main(){

    solve();

}
