#include<bits/stdc++.h>
using namespace std;

vector<vector<vector<int>>> dp;

int find(int i,int j,vector<int> &arr, int k)
{
    if(k==0)
    {
        return dp[i][j][k]=0;
    }

    int mx=0;
    
    if (arr[i] == arr[j])
    {
        mx=max((find(i+1,j,arr,k-1)+arr[i]),(find(i,j-1,arr,k-1)+arr[j]));
    }
    else if(arr[i] > arr[j]){
        mx=(arr[i]+find(i+1,j,arr,k-1));
    }
    else {
        mx=(arr[j]+find(i,j-1,arr,k-1));
    }

    return dp[i][j][k]=mx;
}

int getMaximumCandies(vector<int> arr, int k) 
{
    dp=vector<vector<vector<int>>> (arr.size(),vector<vector<int>>(arr.size(),vector<int>(k,-1)));
    int ans = find(0,arr.size()-1,arr,k);
    return ans;
}


int main()
{
   vector<int> arr={1,2,5,8,1};
   int k=3;
   cout<<getMaximumCandies(arr,k)<<endl;
}