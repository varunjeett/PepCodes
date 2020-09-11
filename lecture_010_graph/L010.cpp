#include <iostream>
#include <vector>

using namespace std;

class Edge{
    
    public :
    
    int v;//destination
    int w; //weight

    Edge(int v, int w){
      this->v=v;
      this->w=w;
    }
 
};

int N=7;// vertices
vector<vector<Edge>> graph(N,vector<Edge>());

void addEdge(int u,int v,int w){
    
   graph[u].push_back(Edge(v,w));
   graph[v].push_back(Edge(u,w));
    
}

void display(){
    
    cout<<endl;
    for(int i=0; i < graph.size(); i++){
        cout<<i<<" -> ";
        for(int j=0; j < graph[i].size(); j++){
            Edge e=graph[i][j];
            cout<<"("<<e.v<<","<<e.w<<")";
        }
        cout<<endl;
    }

}

int findEdge(int r,int c){   //rth node se cth node  
      
    for(int i=0; i < graph[r].size(); i++){
        Edge e=graph[r][i];
        if(e.v == c){
            return i;
        }
    }
    return -1;              

}

void removeEdge(int u,int v){

    int idx1=findEdge(u,v);
    if(idx1!=-1)
        graph[u].erase(graph[u].begin() + idx1);
   

    int idx2=findEdge(v,u);
    if(idx2!=-1)
        graph[v].erase(graph[v].begin() + idx2);   
   
}

void removeVtx(int vtx){
     
    while(graph[vtx].size()!=0)
    {  
       Edge e=graph[vtx][0];
       removeEdge(vtx, e.v);
    }
    
}

void graphConstruct(){
 
 addEdge(0,1,10);
 addEdge(0,3,10);
 addEdge(1,2,10);
 addEdge(2,3,40);
 addEdge(3,4,2);
 addEdge(4,5,2);
 addEdge(4,6,3);
 addEdge(5,6,18);

 display();
 cout<<endl;
}

bool haspath(int src,int des,vector <bool>& arr){
    if(src==des){
        return true;
    }
    arr[src]=true;
    bool res=false;

    for(int i=0; i < graph[src].size(); i++){
        Edge e=graph[src][i];
        if(!arr[e.v]){
            res=res || haspath(e.v, des, arr);
        }
    }
    arr[src]=false;
    return res;
}

int allPath(int src,int des,vector<bool>& arr,string ans)
{   
    if(src==des){
       cout<<ans<<des<<endl;
       return 1;       
    }

    arr[src]=true;
    int count=0;

    for(int i=0; i < graph[src].size(); i++){
        Edge e=graph[src][i];
        if(!arr[e.v]){
           count+=allPath(e.v, des, arr, ans+to_string(src)+"->");    
        }
    }

    arr[src]=false;
    return count;

}

class ansPair
{
    public:
        int heavy=0;
        int light=1e7;;
        int floor=0;;
        int ceil=1e7;
};

void allSolution(int src, int dest, vector<bool> &vis, int w, string ans, ansPair &pair, int data)
{
    if (src == dest)
    {  

       ans = ans + " "+ to_string(dest);
       cout<<ans<<endl;

       pair.heavy=max(pair.heavy,w);
       pair.light=min(pair.light,w);

       if(w>data)
       {
           pair.ceil=min(pair.ceil,w);
       }

       if(w<data)
       {
           pair.floor=max(pair.floor,w);
       }

       return;
    }

    vis[src] = true;

    for (Edge e : graph[src])
    {
        if (!vis[e.v])
            allSolution(e.v, dest, vis, w + e.w, ans + to_string(src) + " ", pair,data);
    }

    vis[src] = false;
}

void question(){

    // vector <bool>arr(N,false);
    // if(haspath(7,7,arr))
    //    cout<<"found";
    
    // cout<<allPath(0,6,arr,"");

    ansPair obj;
    allSolution(0,6,arr,0,"",obj,30);
    cout<<obj.heavy<<" "<<obj.light<<" "<<" "<<obj.floor<<" "<<obj.ceil<<endl;

}

void basic(){ 
    removeEdge(3,4);    
    display();
    removeVtx(6);
    display(); 
}

void solve(){
   graphConstruct();
   //basic();
   question();
}

int main(){

    solve();
    
}