#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//10 may ,optimise water , mr president , journey to the moon

int findpar(int vtx , vector<int>& par)
{
    if(par[vtx]==vtx)
        return vtx;
    par[vtx] = findpar(par[vtx],par);
    return par[vtx];
}

void mergeset( int p1 , int p2, vector<int>&par , vector<int>& countrysize )
{
    if( countrysize[p1] < countrysize[p2] )
    {
       par[p1] = p2;
       countrysize[p2] += countrysize[p1];
    }
    else
    {
       par[p2] = p1;
       countrysize[p1] += countrysize[p2];
    }
}

int journeyToMoon(int n, vector<vector<int>>& astronaut) {
   
    int i;
    int p1,p2;
    vector <int> par ;
    vector <int> countrysize(n,1);
   
    for(i = 0 ; i<n ; i++)
    {
       par.push_back(i);
    }
   

    for(i = 0 ;i < astronaut.size(); i++)
    {
        p1 = findpar(astronaut[i][0] , par);
        p2 = findpar(astronaut[i][1] , par);
      
        if(p1!=p2)
        {
         mergeset(p1,p2,par,countrysize);
        }
    }

    int total = n;
    int ans= 0;
   
    for(i = 0 ; i<n && (total!=0) ; i++)
    {
       if(par[i]==i)
       {
        total = total - countrysize[i];
        ans = ans + (total * countrysize[i]);
       }
    }
    
    return ans;

}

int mrPresident()
{  
   int i;
   long long int n , m , k;
   long long int a , b , c;
   vector < vector <int> > roads , newroads ;
   
   cin>>n>>m>>k;

   long long int cost = 0 ;
  
   for( i = 0 ; i< m ; i++ )
   {
      cin>>a>>b>>c;
      cost+=c;
      roads.push_back({a,b,c});
   }
   
   if(cost<k)
   {
       return 0;  //initially hi cost satisfy
   }

   //call mst
   sort(roads.begin(),roads.end(), [](vector <int> & a,vector<int> & b)
   {
       return a[2] < b[2];  //this - other is decresing
   }
   );

   vector <int> par ;
   for(i= 0; i<=n ; i++ )
   {
      par.push_back(i);
   }
   
    cost  = 0;
   
    for(i= 0; i < m ; i++ )
    {
       a = findpar(roads[i][0],par);
       b = findpar(roads[i][1],par);
     
       if(a!=b)
       {
           cost+=roads[i][2];
           par[a] = b;
           newroads.push_back(roads[i]);
       }  
    }
    
    // for(i = 0 ; i < newroads.size() ; i++)
    // {  
    //     cout<<newroads[i][0]<<newroads[i][1]<<newroads[i][2]<<endl;
    // }

    int component = 0;
    for(i= 1; i<=n ; i++ )
    {
       if(par[i] == i)
          {
              component++;
              if(component>1) return -1;
          }
    }

    if(cost<k)
    {
       return 0;  //mst ke baad hi cost satisfy
    }
    
    int change = 0;
    
    for( i = newroads.size()-1 ; i>=0 ; i-- )
    {
      if( cost <= k ) break; 
      
      cost = cost - newroads[i][2] + 1;
      ++change ; 
    }
     
    return cost <= k ? change : -1;

    

}

int lc1168(int n , vector <int>& wells, vector< vector<int>>& pipes )
{   
    int i,p1,p2;

    int cost = 0;

    for(i = 0 ; i < n ; i++)
    {
       pipes.push_back( {i+1,0,wells[i]} );   //naya node 0 create krlia 
    }
    
    //sort the pipes================================================
    //??
    sort(pipes.begin(), pipes.end(), [](vector<int> &a, vector<int> &b)
    {
        return a[2] < b[2];
    }
    );
    
    vector <int> par;

    for(i = 0;i<=n;i++)
    {
       par.push_back(i);
    }
     
    for(i=0;i<pipes.size();i++)
    {
       p1=findpar( pipes[i][0] , par );
       p2=findpar( pipes[i][1] , par );

       if(p1!=p2)
       {   
           cost+=pipes[i][2];
           par[p1]=p2;
       }
    }
    
    return cost;

}

void lc1168_()
{

  vector < int > wells = {1,2,2,3,2}; 
  vector < vector <int> > pipes = { {1,2,1},{2,3,1},{4,5,7} };
  cout << lc1168(wells.size(),wells,pipes);
}

void journeymoon()
{
   int n , p , i;
   int a , b;
   vector<vector<int>> astronaut;

   cin>>n>>p;
   
   for(i =0 ; i< p; i++ )
   {
    cin>>a>>b;
    astronaut.push_back( {a,b} );
   }
   cout<<journeyToMoon(n,astronaut);
   
}

void solve()
{ 
    // lc1168_();
    //journeymoon();
    cout<<mrPresident();

}

int main()
{
    solve();
}
