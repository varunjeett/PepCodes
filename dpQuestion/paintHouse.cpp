//based on include ,exclude type questions::::
// There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. 
// The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color, 
// and you need to cost the least. Return the minimum cost.


class Solution {
public:

    int minCost(vector<vector<int>> &arr) 
    {
        // write your code here
        int N=arr.size();
        if(N==0)
        return 0;
        
        vector<vector<int>> dp(3,vector<int>(N,0));
        
        // dp [0] for red , [1] for  green , [2] for blue
        
        for(int n=0;n<N;n++)
        {
            if(n==0)
            {
                dp[0][n]=arr[n][0];
                dp[1][n]=arr[n][1];
                dp[2][n]=arr[n][2];
                continue;
            }
            
            dp[0][n]=arr[n][0]+min(dp[1][n-1],dp[2][n-1]);//paint it red
            dp[1][n]=arr[n][1]+min(dp[0][n-1],dp[2][n-1]);//paint it green
            dp[2][n]=arr[n][2]+min(dp[0][n-1],dp[1][n-1]);//paint it blue
            
        }
        
        return min(dp[0][N-1],min(dp[1][N-1],dp[2][N-1]));
    }
};