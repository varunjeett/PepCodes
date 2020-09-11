#include <bits/stdc++.h>

using namespace std;

// vector<vector<int>> result;
// void permute_(vector<int> &nums, vector<int> &ans)
// {
//     if (ans.size() == nums.size())
//     {
//         result.push_back(ans);
//         return;
//     }

//     int vis = 0;
//     for (int i = 0; i < nums.size(); i++)
//     {
//         int mask = (1 << i);
//         if ((vis & mask) == 0)
//         {
//             vis ^= mask;
//             ans.push_back(nums[i]);
//             permute_(nums, ans);
//             ans.pop_back();
//             vis ^= mask;
//         }
//     }
//     return;
// }

// void permute(vector<int> &nums)
// {
//     vector<int> ans;
//     permute_(nums, ans);
//     for (int i = 0; i < result.size(); i++)
//     {
//         for (int j = 0; j < result[0].size(); j++)
//         {
//             cout << result[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

// void set3()
// {
//     vector<int> num = {1, 2, 3};
//     permute(num);
// }

// int friends_pairing_problem_DP(int n, vector<int> &dp)
// {
//     int N = n;
//     for (int n = 0; n <= N; n++)
//     {
//         if (n <= 1)
//         {
//             dp[n] = 1;
//             continue;
//         }

//         int single = dp[n - 1];           //friends_pairing_problem(n - 1, dp);
//         int pairUp = dp[n - 2] * (n - 1); //friends_pairing_problem(n - 2, dp) * (n - 1);

//         dp[n] = (single + pairUp);
//     }
//     return dp[N];
// }


int main()
{
    // int n = 100;
    // vector<int> dp(n + 1, 0);
    // cout << friends_pairing_problem_DP(n, dp);
    //set3();

}