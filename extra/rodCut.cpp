#include <bits/stdc++.h>
using namespace std;

int f1(int l,vector<int> &a,vector<int> &dp)
{
    if(l==1)    //o1
    return dp[l]=a[l-1];

    if(dp[l]!=-1)   //o1
    return dp[l];
    
    int mx=a[l-1];  //o1

    //o(l)
    for(int c=1;c<=(l/2);c++)
    {
        int  p1=f1(c,a,dp);
        int  p2=f1(l-c,a,dp);

        mx=max(mx,(p1+p2));
    }

    return dp[l]=mx;
}


int main()
{
    vector<int> a={1, 5, 8, 9, 10, 17, 17, 20};
    vector<int> dp(a.size()+1,-1);
    int rt;
    rt=f1(a.size(),a,dp);
    cout<<rt<<endl;
}
