//bus route , union find  , 3 may
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;


class Node{
    
    int v;

    Node(int v1){
        this->v=v1;
    }
};

int n=7;

vector < vector<int> > graph(n,vector<int>() );

void addEdge(int u,int v)
{
    graph[u].push_back(v);
}

void display()
{
    for(int i=0;i<n;i++)
    {   cout<<i<<"->";
        for(int j=0;j<graph[i].size();j++)
        {
            cout<<graph[i][j]<<",";
        }
        cout<<endl;
    }
}

void construct()
{
    addEdge(1,0);
    addEdge(1,2);
    addEdge(0,3);
    //addEdge(3,2);
    addEdge(2,4);
    addEdge(5,6);
    addEdge(4,5);
    addEdge(4,6);
    
    display();

}

vector < vector < int > > edgeList()
{
   vector < vector < int > > ret;
   for(int i=0;i<n;i++)
    {   
        for(int j=0;j<graph[i].size();j++)
        {
            vector < int > edge={i,graph[i][j]};
            ret.push_back(edge);                            //i hai ek aur dusra graph[i][j]
        }
    }

   return ret;
}

int findLeader(int vtx,vector < int >& par) 
{
   if(par[vtx]==vtx) return vtx;

   return par[vtx]=findLeader(par[vtx],par) ;  

}

bool mergeSet(int u,int v,vector < int >& par,vector < int >& setSize)
{
   
   int l1=findLeader(u,par);
   int l2=findLeader(v,par);
   
   if(l1==l2) return true;
   
   else
   {
        if(setSize[l1]>setSize[l2])
        {
       par[l2]=l1;
       setSize[l1]+=setSize[l2];
       }

       else
       {
       par[l1]=l2;
       setSize[l2]+=setSize[l1]; 
       }
   }
   
   return false;
   
}

vector < int > findCycle (vector < vector < int > >& edge)
{
    vector < int > par;

    for(int i=0;i<edge.size();i++)
    {
        par.push_back(i);
    }
 
    vector < int > setSize(edge.size(),1);

    bool res= false;
    
    int i=0;
    for( i=0;i<edge.size() && (!res);i++)
    {   
        res = res || mergeSet(edge[i][0],edge[i][1],par,setSize);
    }
    
    if(res) return {edge[i-1][0],edge[i-1][1]};
    else
       return {};
    
}

void unionFind01(){
   
   construct();
   vector < vector < int > > res=edgeList();
   vector < int > ans=findCycle(res); 
   cout<<ans[0]<<","<<ans[1]<<endl;   
}

//void unionFind02(){;}

void unionFind()
{
    unionFind01();
    //unionFind02();    
}

int numBusesToDestination(vector<vector<int>>& routes, int s, int t) {

    if(s==t)  return 0;

    unordered_map < int, vector <int> > map;
   
    unordered_set < int > st;
    
    for (int i = 0; i < routes.size(); i++)
    {
        for (int ele : routes[i])
        {
            map[ele].push_back(i);
        }
    }

    queue <int> q;
    q.push(s);
    st.insert(s);
    
    int level=0;
    int cursize=0;
    
    vector <bool> visRoute(routes.size(),false);

    while( q.size()!=0 )
    {
        cursize = q.size();
        
        while (cursize-- > 0)
        
        {
        
         int rvtx = q.front(); q.pop();
         
         if( rvtx == t)  return level;
                
         for(int i:map[rvtx])
         { 
            if(visRoute[i])
                continue;
        
            for(int j=0;j<routes[i].size();j++) 
            {
                if ( st.count(routes[i][j]) == 0 )  
                { 
                    q.push(routes[i][j]);
                    st.insert(j);
                }
            }
            visRoute[i]=true;   
         }

        } 
        level++;
        
    }

    return -1;

}

void busroute()
{
   vector<vector<int>> routes = { {1,2,7},{3,6,7} };
   int s=1;
   int t=6;
   
   int res = numBusesToDestination(routes,s,t);
   
   cout<<res<<endl;

}

string lc1061(string A,string B,string C)
{
    vector<int>par;
    
    for(int i=0;i<26;i++)  par.push_back(i);

    for(int i=0;i<A.length();i++)
    {
        int p1=findLeader(A[i]-'a',par);

        int p2=findLeader(B[i]-'a',par);

        par[p1]=min(p1,p2);  //merge
        par[p2]=min(p1,p2);  //merge

    } 

    string ans="";
   
    for(int i=0;i<C.length();i++)
    {  //here we ll do path compression for the remaining
       ans = ans + (char)( findLeader(C[i]-'a',par) + 'a' ) ;
    }
    
    return ans;

}


int main(){
          
    //busroute();
    cout<<lc1061("hello","world","hold");
    //unionFind();
  
}
