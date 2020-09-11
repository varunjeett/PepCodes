//count of all binary string of length N with no consecutive zeroes 
#include <bits/stdc++.h>

using namespace std;

int countBS(int N)
{
    vector<vector<int>> dp(2,vector<int>(N+1,0));
    for(int n=0;n<=N;n++)
    {
        if(n<=1)
        {
            dp[0][n]=n;
            dp[1][n]=n;            
            continue;
        }

        //count of required string of length n ending at 0 
        int end_zero=dp[1][n-1];// n-1 length ke '1' end hone wale ke peeche lga dia, as dont want consecutive zeroes
        

        //count of required string of length n ending at 1
        int end_one=dp[0][n-1]+dp[1][n-1];// n-1 length ke '1' or '0' pe  end hone wale ke peeche lga dia.

        dp[0][n]=end_zero;
        dp[1][n]=end_one;
    }

    return dp[1][N]+dp[0][N];
}


//count of all binary string of length N with no consecutive ones 
int countBS2(int N)
{
    vector<vector<int>> dp(2,vector<int>(N+1,0));
    for(int n=0;n<=N;n++)
    {
        if(n<=1)
        {
            dp[0][n]=n;
            dp[1][n]=n;            
            continue;
        }

        //count of required string of length n ending at 0 
        int end_zero=( ((dp[0][n-1]% 1000000007)+(dp[1][n-1] % 1000000007))  % 1000000007 );// n-1 length ke '1' end hone wale ke peeche lga dia, as dont want consecutive zeroes
        
        //count of required string of length n ending at 1
        int end_one=(dp[0][n-1]% 1000000007);// n-1 length ke '1' or '0' pe  end hone wale ke peeche lga dia.

        dp[0][n]=end_zero;
        dp[1][n]=end_one;
    }

    return (((dp[1][N]% 1000000007)+(dp[0][N]% 1000000007))% 1000000007);
}


int main()
{
    int N=8;
    cout<<countBS(N);
}