// 121. Best Time to Buy and Sell Stock
// If you were only permitted to complete at most one transaction 
// (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
class Solution {
public:
    int maxProfit(vector<int>& p) {
        int n=p.size();
        if(n==0)
            return 0;
        vector<int> a(n,0);
        a[0]=p[0];
        int mn=p[0];
        for(int i=1;i<n;)
        {
            mn=min(mn,p[i]);
            a[i++]=mn;
        }
        
        
        int ans=0;
        for(int i=0;i<n;i++)
        {
            ans=max(ans,(p[i]-a[i]));
        }
        
        return ans;
        
    }    
};

// 122. Best Time to Buy and Sell Stock II(infinite non overlapping transactions)
//greediness: key point is to cash all the upstrokes(all the cases wherever sell point is greater than buy price), so that max profit can be collected
//concept of previus index tk ka profit nikal lo aur fr apna max nikalo, by previous min value will cause overlap, as that buying point can be previously used by some other selling point

class Solution {
public:
    int maxProfit(vector<int>& a) {
        int n=a.size();
        if(n==0)
            return 0;
        
        a.push_back(0);
        
        int b=0;
        int s=0;
        int total=0;
        while(s < n)
        {
            if(a[s] <= a[s+1])
                s++;
            else
            {
                total+=max(0,a[s]-a[b]);
                s++;
                b=s;
            }
        }
        
        return total;
    }
};


// 123. Best Time to Buy and Sell Stock III
// Design an algorithm to find the maximum profit. You may complete at most two transactions.
