#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

int find(vector< vector<int> > &temp)
{
    int mn=INT_MAX;
    
    for(int i=0;i<temp.size();i++)
    {
        for(int j=i+1;j<temp.size();j++)
        {
            int x1=temp[i][0];
            int y1=temp[i][1];
            
            int x2=temp[j][0];
            int y2=temp[j][1];
            
            int dis=((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
            
            dis=pow(dis,0.5);
            
            dis=min(dis,mn);
        }
    }
    
    return mn;
}


int main()
{
	// Write your code here
	int n;
	cin>>n;
	
	vector< vector<int> >arr( n,vector<int>(2,0) );

	int i=0;
	while(i!=n)
	{
	    int a,b;
	    cin>>a>>b;
	    arr[i][0]=a;
	    arr[i][1]=b;
	    i++;
	}

	
	vector< vector<int> > trips;
	int t;
	cin>>t;
	i=0;
	while(i!=t)
	{
	   int type;
	   cin>> type;
	   if(type==1 || type==2)
	   {
	       int a,b;
	       cin>>a>>b;
	       trips.push_back({type,a,b});
	   }
	   else
	   {
	       int a,b,c,d;
	       cin>>a>>b>>c>>d;
	       trips.push_back({type,a,b,c,d});
	   }
	   
	   i++;
	}

    for(int i=0;i<trips.size();i++)
    {
        vector<int> tt=trips[i];
        
        int type=tt[0];
        
        if(type==1)
        {
            int x1=tt[1];
            int x2=tt[2];
            
            vector< vector<int> >temp;
            
            for(int i=0;i<arr.size();i++)
            {
                vector<int> ele = arr[i];
                if(ele[0] > x1 && ele[0] < x2)
                {
                    temp.push_back(ele);
                }
            }
            
            
            int ans=find(temp);
            cout<<ans<<" ";
        }
        
        
        else if(type==2)
        {
            int y1=tt[1];
            int y2=tt[2];
            
            vector< vector<int> >temp;
            
           for(int i=0;i<arr.size();i++)
            {
                vector<int> ele = arr[i];
                
                if(ele[1] > y1 && ele[0] < y2)
                {
                    temp.push_back(ele);
                }
            }
            
            int ans=find(temp);
            cout<<ans<<" ";
        }
        
        else
        {
            int x1=tt[1];
            int x2=tt[2];
            int y1=tt[3];
            int y2=tt[4];
            vector< vector<int> >temp;
            
            for(int i=0;i<arr.size();i++)
            {
                vector<int> ele = arr[i];
                
                if((ele[0] > x1 && ele[0] < x2) && (ele[1] > y1 && ele[1] < y2))
                {
                    temp.push_back(ele);
                }
            }
            
            int ans=find(temp);
            cout<<ans<<" ";
            
        }
    }
    
	return 0;
}