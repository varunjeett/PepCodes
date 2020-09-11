class Solution {
public:
    
    int numWays(int N, int K) {
        // write your code here
        if(N==0 || K==0)
            return 0;
            
        vector<vector< pair<int,int> >> dp(K,vector<pair<int,int>>(N+1,{0,0}));
        
        
        //each cell of dp is a pair
        //first value of pair, is the total no of ways following our rules and ending at that color
        //second value of pair is the subset of ways with two same colors at the ending so subtract it for the next house
        int sum=K;
        
        for(int n=0;n<=N;n++)
        {
            if(n<=1)
            {
                for(int k=0;k<K;k++)
                {
                    dp[k][n]={n,0};
                }
                
                continue;
            }
            
            //for n=3 k=2,(red or green)
            
            //for n=3, we use n-1 state:
            //we have RR,GR for k=0
            //we have RG,GG for k=1
            
            //paint 3rd house with red: RGR, GGR, GRR,
            //paint 3rd house with green: RRG, GRG, RGG,
            
            int nsum=0;
            for(int k=0;k<K;k++)
            {
                pair<int,int> prevSame=dp[k][n-1];
                dp[k][n]={(sum-prevSame.second),(prevSame.first-prevSame.second)};
                nsum+=dp[k][n].first;
            }
            sum=nsum;
        }
        
        return sum;
    }
};