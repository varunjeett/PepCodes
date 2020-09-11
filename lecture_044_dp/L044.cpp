#include <iostream>
#include <vector>

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

int combi_fini_memo(vector<int> &coins, int idx, int tar, vector<vector<int>> &dp)
{
    if (tar == 0 || idx == coins.size())
    {
        if (tar == 0)
            return dp[idx][tar] = 1;
        return dp[idx][tar] = 0;
    }

    if (dp[idx][tar] != -1)
        return dp[idx][tar];

    int count = 0;
    if (tar - coins[idx] >= 0)
        count += combi_fini_memo(coins, idx + 1, tar - coins[idx], dp);

    count += combi_fini_memo(coins, idx + 1, tar, dp);
    return dp[idx][tar] = count;
}

int combi_fini_dp(vector<int> &coins, int IDX, int TAR, vector<vector<int>> &dp)
{
    for (int tar = 0; tar <= TAR; tar++)
    {
        for (int idx = IDX; idx >= 0; idx--)
        {
            if (tar == 0)
            {
                dp[idx][tar] = 1;
                continue;
            }

            if (idx == IDX)
            {
                dp[idx][tar] = 0;
                continue;
            }

            int count = 0;
            if (tar - coins[idx] >= 0)
                count += dp[idx + 1][tar - coins[idx]];
            count += dp[idx + 1][tar];

            dp[idx][tar] = count;
        }
    }
    return dp[0][TAR];
}

int combi_fini_memo_02(vector<int> &coins, int idx, int tar, vector<vector<int>> &dp)
{
    if (tar == 0 || idx == 0)
    {
        if (tar == 0)
        {
            return dp[idx][tar] = 1;
        }
        return dp[idx][tar] = 0;
    }

    if (dp[idx][tar] != -1)
        return dp[idx][tar];

    int count = 0;
    if (tar - coins[idx - 1] >= 0)
    {
        count += combi_fini_memo_02(coins, idx - 1, tar - coins[idx - 1], dp);
    }
    count += combi_fini_memo_02(coins, idx - 1, tar, dp);

    return dp[idx][tar] = count;
}

int combi_fini_tab_02(vector<int> &coins, int IDX, int TAR, vector<vector<int>> &dp)
{
    for (int idx = 0; idx <= IDX; idx++)
    {
        for (int tar = 0; tar <= TAR; tar++)
        {
            if (tar == 0 || idx == 0)
            {
                if (tar == 0)
                {
                    dp[idx][tar] = 1;
                    continue;
                }
                dp[idx][tar] = 0;
                continue;
            }

            int count = 0;
            if (tar - coins[idx - 1] >= 0)
            {
                count += dp[idx - 1][tar - coins[idx - 1]];
            }
            count += dp[idx - 1][tar];

            dp[idx][tar] = count;
        }
    }

    return dp[IDX][TAR];
}

int getPathFromDP(vector<int> &coins, int idx, int tar, string ans, vector<vector<int>> &dp)
{
    if (tar == 0 || idx == 0)
    {
        if (tar == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    if (tar - coins[idx - 1] >= 0 && dp[idx - 1][tar - coins[idx - 1]])
    {
        count += getPathFromDP(coins, idx - 1, tar - coins[idx - 1], ans + to_string(coins[idx - 1]) + " ", dp);
    }

    if (dp[idx - 1][tar])
    {
        count += getPathFromDP(coins, idx - 1, tar, ans, dp);
    }

    return count;
}

int knapsack_memo(vector<int> &w, vector<int> &p, int weight, int n, vector<vector<int>> &dp)
{
    if (weight == 0 || n == 0)
    {
        return dp[n][weight] = 0;
    }

    if (dp[n][weight] != -1)
    {
        return dp[n][weight];
    }

    int max_ = 0;
    if (weight - w[n - 1] >= 0)
    {
        max_ = max(max_, knapsack_memo(w, p, weight - w[n - 1], n - 1, dp) + p[n - 1]);
    }
    max_ = max(max_, knapsack_memo(w, p, weight, n - 1, dp));

    return dp[n][weight] = max_;
}

int UNBOUNDEDknapsack_memo(vector<int> &w, vector<int> &p, int weight, int n, vector<vector<int>> &dp)
{
    if (weight == 0 || n == 0)
    {
        if (weight == 0)
        {
            return dp[n][weight] = 0;
        }
        return dp[n][weight] = 1e7;
    }

    if (dp[n][weight] != -1)
    {
        return dp[n][weight];
    }

    int min_ = 1e7;
    if (weight - w[n - 1] >= 0)
    {
        min_ = min(min_, knapsack_memo(w, p, weight - w[n - 1], n, dp) + p[n - 1]);
    }
    min_ = min(min_, knapsack_memo(w, p, weight, n - 1, dp));

    return dp[n][weight] = min_;
}

//leetcode 416: tabulation is slower

// class Solution {
// public:
//     bool canPartition(vector<int>& nums) {
//         int n=nums.size();
//         int target=0;
//         for(int ele:nums) {
//             target+=ele;
//         }
//         if((target%2)!=0)
//             return false;
//         vector<vector<int>> dp(nums.size()+1,vector<int>((target/2)+1,-1));
//         return part(target/2,nums,dp);
        
//     }
    
//     int part(int CUR, vector<int>& nums,vector<vector<int>>& dp) {
        
//         for(int cur=0; cur<=CUR; cur++) {
            
//             for(int idx=nums.size(); idx>=0; idx--) {
                
//              if(cur==0 || idx==nums.size()) {
                  
//                   if(cur==0)
//                   {
//                       dp[idx][cur]=1;
//                       continue;
//                   }
                    
//                  dp[idx][cur]=0;
//                  continue;
//              }
        
//              bool res=false;
//              if(cur-nums[idx] >=0)
//                 res = res || (dp[idx+1][cur-nums[idx]]==1);
//              res=res || (dp[idx+1][cur]==1);
        
//              dp[idx][cur]=(res==true) ? 1 : 0;

//             }
//         }
        
//         return (dp[0][CUR]==1 ) ? true: false;
//     }
// };

//Leetcode 416
bool canPartition_(vector<int> &nums, int n, int sum, vector<vector<int>> &dp)
{
    if (sum == 0 || n == 0)
    {
        if (sum == 0)
            return dp[n][sum] = 1;
        return dp[n][sum] = 0;
    }

    if (dp[n][sum] != -1)
        return dp[n][sum];

    bool res = false;
    if (sum - nums[n - 1] >= 0)
        res = res || canPartition_(nums, n - 1, sum - nums[n - 1], dp) == 1;
    res = res || canPartition_(nums, n - 1, sum, dp) == 1;

    return dp[n][sum] = res ? 1 : 0;
}

bool canPartition(vector<int> &nums)
{
    int sum = 0;
    for (int ele : nums)
        sum += ele;
    if (sum % 2 != 0)
        return false;

    sum /= 2;
    vector<vector<int>> dp(nums.size() + 1, vector<int>(sum + 1, -1));

    return canPartition_(nums, nums.size(), sum, dp);
}

void targetType()
{
    vector<int> coins = {3, 5};
    int target = 7;
    // vector<vector<int>> dp(coins.size() + 1, vector<int>(target + 1, -1));
    // cout << combi_fini_memo(coins, 0, target, dp);
    // int ans = combi_fini_memo(coins, coins.size(), target, dp);
    // display2D(dp);
    // cout << ans;

    // vector<vector<int>> dp(coins.size() + 1, vector<int>(target + 1, -1));
    // int ans = combi_fini_memo_02(coins, coins.size(), target, dp);
    // display2D(dp);
    // cout << ans;

    vector<vector<int>> dp(coins.size() + 1, vector<int>(target + 1, -1));
    int ans = combi_fini_tab_02(coins, coins.size(), target, dp);
    display2D(dp);
    cout << ans << endl;

    cout << getPathFromDP(coins, coins.size(), target, "", dp);
}

void knapsack()
{
    vector<int> p = {10, 40, 50, 70};
    vector<int> w = {1, 3, 4, 5};
    int weight = 8;
    int n = w.size();
    vector<vector<int>> dp(n + 1, vector<int>(weight + 1, -1));
    int ans = UNBOUNDEDknapsack_memo(w, p, weight, n, dp);
    display2D(dp);
    cout << ((ans == 1e7) ? -1 : ans);
}

int findWays(vector<int> &nums, int S, int cur, int idx, vector<vector<int>> &dp)
{
    if (idx == 0)
    {
        if (cur == S)
            return dp[idx][cur] = 1;
        return dp[idx][cur] = 0;
    }
    if (dp[idx][cur] != -1)
        return dp[idx][cur];

    int count = 0;
    count += findWays(nums, S, cur + nums[idx - 1], idx - 1, dp);
    count += findWays(nums, S, cur - nums[idx - 1], idx - 1, dp);

    return dp[idx][cur] = count;
}

int findTargetSumWays(vector<int> &nums, int S)
{
    int sum = 0;
    for (int ele : nums)
        sum += ele;
    vector<vector<int>> dp(nums.size() + 1, vector<int>(2 * sum + 1, -1));
    int ans = findWays(nums, S + sum, 0 + sum, nums.size(), dp);
    display2D(dp);
    return ans;
}

void lc494()
{
    vector<int> nums = {1, 1, 1, 1, 1};
    int S = 3;
    cout << findTargetSumWays(nums, S);
}

int findMin_memo(string word1, string word2, int n, int m, vector<vector<int>> &dp)
{
    if (n == 0 || m == 0)
    {
        int ret = 0;
        if (n == 0) // consider (c,abc) now aftr c,we need to add ab in front that is M operations
        {
            ret = m;
        }
        else //(abc,c) we have to remove ab, hence n operations
        {
            ret = n;
        }
        return dp[n][m] = ret;
    }

    if (dp[n][m] != -1)
        return dp[n][m];

    int ans;
    if (word1[n - 1] == word2[m - 1])
        ans = findMin_memo(word1, word2, n - 1, m - 1, dp);
    else
    {
        int ins = findMin_memo(word1, word2, n, m - 1, dp);
        int rep = findMin_memo(word1, word2, n - 1, m - 1, dp);
        int del = findMin_memo(word1, word2, n - 1, m, dp);
        ans = min(min(ins, rep), del) + 1;
    }
    return dp[n][m] = ans;
}

int minDistance(string word1, string word2)
{

    int n = word1.length();
    int m = word2.length();
    if (n == 0 || m == 0)
        return n == 0 ? m : n;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return findMin_memo(word1, word2, n, m, dp);
}

int minDistance_tab(string word1, string word2)
{
    int N = word1.length();
    int M = word2.length();
    if (N == 0 || M == 0)
        return N == 0 ? M : N;

    vector<vector<int>> dp(N + 1, vector<int>(M + 1, -1));

    for (int n = 0; n <= N; n++)
    {
        for (int m = 0; m <= M; m++)
        {
            if (n == 0 || m == 0)
            {
                int ret = 0;
                if (n == 0) // consider (c,abc) now aftr c,we need to add ab in front that is M operations
                {
                    ret = m;
                }
                else //(abc,c) we have to remove ab, hence n operations
                {
                    ret = n;
                }
                dp[n][m] = ret;
                continue;
            }

            int ans;
            if (word1[n - 1] == word2[m - 1])
                ans = dp[n - 1][m - 1];
            else
            {
                int ins = dp[n][m - 1];
                int rep = dp[n - 1][m - 1];
                int del = dp[n - 1][m];
                ans = min(min(ins, rep), del) + 1;
            }
            dp[n][m] = ans;
        }
    }

    return dp[N][M];
}

void lc72()
{
    string word1 = "horse";
    string word2 = "ros";
    cout << minDistance_tab(word1, word2);
}

void solve()
{
    // targetType();
    //knapsack();
    // lc494();
    lc72();
}

int main()
{
    solve();
}

