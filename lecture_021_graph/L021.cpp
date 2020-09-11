//A point and bridge
#include <iostream>
#include <vector>

using namespace std;

int N=7;
int timer=0;

vector <int> par(N,0);
vector <int> dis(N,0);
vector <int> low(N,0);
vector <bool> vis(N,false);
vector <int> A_Pt(N,0);

int DFS(int parent,int current,vector<vector<int>>& graph) {
    
    int rootcalls=0;

    par[current] = parent;

    dis[current]=low[current]=timer++;

    vis[current]=true;

    for( int i=0 ; i < graph[current].size();i++ )
    {        
        int childOfCur=graph[current][i];
        
        if(!vis[childOfCur]) 
        {
            if(par[current]==-1) 
                rootcalls++;     

            DFS(current,childOfCur,graph);
            
            if(dis[current] <= low[childOfCur])
               A_Pt[current]++;
            
            if(dis[current] < low[childOfCur])
              cout << "AP Bridge: " << current << " to " << childOfCur << endl;

            low[current]=min(low[childOfCur],low[current]);
        }

        else
        {
            if(par[current]!=childOfCur) {
               low[current] = min(dis[childOfCur],low[current]); 
            }
        }
        
    }

    return rootcalls;
}

void AP(int start,vector<vector<int>>& graph){
  
    int calls=DFS(-1 ,start, graph);
    cout<<"calls"<<calls<<endl;
    if(calls==1) {
       A_Pt[start]--;
    }

    for(int i= 0;i<A_Pt.size();i++)
    {
       cout<<i<<" , "<<A_Pt[i]<<endl;
    }
}

void addEdge(int first, int second,vector<vector<int>>& graph){

    graph[first].push_back(second);  
    graph[second].push_back(first);

}  

void solve(){
    
    vector <vector<int>> graph(N,vector<int>());

    addEdge(0,1,graph);
    addEdge(1,2,graph);
    addEdge(2,4,graph);
    addEdge(0,3,graph);
    addEdge(3,2,graph);
    addEdge(4,5,graph);
    addEdge(5,6,graph);
    addEdge(6,4,graph);
    addEdge(6,2,graph);
    addEdge(6,1,graph);
    
    for(int i = 0;i<7;i++)  //7 because of number of vertices
    {   
        cout<<i<<"->";

        for(int j = 0;j<graph[i].size();j++)
        {
           cout<<graph[i][j]<<" ";
        }
        cout<<endl;

    }

    AP(0,graph);
   
}

int main(){
    solve();
}