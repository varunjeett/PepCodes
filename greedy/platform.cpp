//minimum platforms , minimum meeting rooms
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void display(vector<int> &arr)
{
    for (int ele : arr)
        cout << ele << " ";
    cout << endl;
}

void display2D(vector<vector<int>> &arr)
{
    for (vector<int> ar : arr)
        display(ar);
    cout << endl;
}

int find(vector<vector<int>> &arr)
{
    sort(arr.begin(),arr.end());   //sorting on the basis of start time
    display2D(arr);
    priority_queue<int,vector<int>,greater<int>> pq; //min priority queue
    
    pq.push(arr[0][1]);           //initial meeting end time
    
    for(int i=1;i<arr.size();i++)
    {
        int st=arr[i][0];
        int ed=arr[i][1];
        
        int rvtx=pq.top();

        if(st > rvtx) 
        {
            pq.pop();
            pq.push(ed);
        }
        else
        {
            pq.push(ed);
        }
    }
    
    return pq.size();
}

int main() {
	//code
	int t;
	cin>>t;
	while(t-- > 0)
	{
	    int l;
	    cin>>l;
        vector<vector<int>> arr(l,vector<int>(2,0));
        
	    int i=0;
	    while(i != l)
	    {
	        cin>>arr[i++][0];
	    }
	    
	    i=0;
	    while(i != l)
	    {
	        cin>>arr[i++][1];
	    }
	    
	    cout<<find(arr)<<endl;
	}
	return 0;
}