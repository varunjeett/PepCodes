#include <iostream>
#include <vector>

using namespace std;

void display_bool(vector<bool> &arr)
{
    for (bool ele : arr)
        cout << ele << " ";
    cout << endl;
}

void display2D_bool(vector<vector<bool>> &arr)
{
    for (vector<bool> ar : arr)
        display_bool(ar);
    cout << endl;
}

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

int longestCommonSubsequence_recur(string &text1, string &text2, int i, int j, int len1, int len2, vector<vector<int>> &dp)
{
    if (i == len1 || j == len2)
        return dp[i][j] = 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int ans = 0;
    if (text1[i] == text2[j])
    {
        ans = longestCommonSubsequence_recur(text1, text2, i + 1, j + 1, len1, len2, dp) + 1;
    }
    else
    {
        ans = max(longestCommonSubsequence_recur(text1, text2, i + 1, j, len1, len2, dp), longestCommonSubsequence_recur(text1, text2, i, j + 1, len1, len2, dp));
    }

    return dp[i][j] = ans;
}

int longestCommonSubsequence_tab(string &text1, string &text2, int len1, int len2, vector<vector<int>> &dp)
{
    for (int i = len1; i >= 0; i--)
    {
        for (int j = len2; j >= 0; j--)
        {
            if (i == len1 || j == len2)
            {
                dp[i][j] = 0;
                continue;
            }

            int ans = 0;

            if (text1[i] == text2[j])
            {
                ans = dp[i + 1][j + 1] + 1;
            }
            else
            {
                ans = max(dp[i + 1][j], dp[i][j + 1]);
            }

            dp[i][j] = ans;
        }
    }

    return dp[0][0];
}

int longestCommonSubsequence(string text1, string text2)
{
    int len1 = text1.length();
    int len2 = text2.length();
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, -1));
    // int ans = longestCommonSubsequence_recur(text1, text2, 0, 0, len1, len2, dp);
    int ans = longestCommonSubsequence_tab(text1, text2, len1, len2, dp);
    display2D(dp);
    cout << ans;
    return 1;
}

//faith is to return the max substring starting from i and j (including both) ;; str1[i]!=str2[j], then it will return 0 and answer is stored in max_;
int max_ = 0;
int longestCommonSubstring_recur(string &text1, string &text2, int i, int j, vector<vector<int>> &dp)
{
    if (i == text1.length() || j == text2.length()) //when one substring is empty, the max possible is 0
        return dp[i][j] = 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    longestCommonSubstring_recur(text1, text2, i + 1, j, dp); //possibility of mx substring  from i+1,j
    longestCommonSubstring_recur(text1, text2, i, j + 1, dp); //possibility of mx substring  from i,j+1

    if (text1[i] == text2[j])
    {
        int val = longestCommonSubstring_recur(text1, text2, i + 1, j + 1, dp) + 1; //it will give mx substring possible from i+1,j+1
        max_ = max(max_, val);
        return dp[i][j] = val;
    }

    return dp[i][j] = 0; //since str1[i]!=str2[j], max ss possible from i and j (including both) ;; will be zero
}

int longestCommonSubstring_tab(string &text1, string &text2)
{
    int count = 0;
    vector<vector<int>> dp(text1.length() + 1, vector<int>(text2.length() + 1, -1));

    for (int i = text1.length(); i >= 0; i--)
    {
        for (int j = text2.length(); j >= 0; j--)
        {
            if (i == text1.length() || j == text2.length())
            {
                dp[i][j] = 0;
                continue;
            }
            int ans = 0;

            if (text1[i] == text2[j])
            {
                ans = dp[i + 1][j + 1] + 1;
                count = max(count, ans);
            }

            dp[i][j] = ans;
        }
    }

    display2D(dp);
    return count;
}

int longestCommonSubstring(string text1, string text2)
{
    int len1 = text1.length();
    int len2 = text2.length();
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, -1));
    longestCommonSubstring_recur(text1, text2, 0, 0, dp);
    display2D(dp);
    cout << max_;

    // int ans = longestCommonSubstring_tab(text1, text2);
    // cout << ans;
    return 1;
}

void substr_subseq()
{
    // longestCommonSubsequence("abcdef", "zbcdy");
    longestCommonSubstring("10001", "10011");
}

int permu_infini_rec(int target, vector<int> &coin, vector<int> &dp)
{
    if (target == 0)
        return dp[target] = 1;
    if (dp[target] != -1)
        return dp[target];

    int count = 0;
    for (int ele : coin)
    {
        if (target - ele >= 0)
            count += permu_infini_rec(target - ele, coin, dp);
    }
    return dp[target] = count;
}

int permu_infini_tab(int target, vector<int> &coin, vector<int> &dp)
{
    int amt = target;
    for (target = 0; target <= amt; target++)
    {
        if (target == 0)
        {
            dp[target] = 1;
            continue;
        }

        int count = 0;
        for (int ele : coin)
        {
            if (target - ele >= 0)
                count += dp[target - ele];
        }
        dp[target] = count;
    }
    return dp[amt];
}

int combi_infini_tab(int target, vector<int> &coin, vector<int> &dp) //each time we are taking one coin(in forwrd direction) and using it in the forward way
{
    int amt = target;

    for (int ele : coin)
    {
        for (target = 0; target <= amt; target++)
        {
            if (target == 0)
            {
                dp[target] = 1;
                continue;
            }

            if (target - ele >= 0)
                dp[target] += dp[target - ele];
        }
    }

    return dp[amt];
}

void coin_change()
{
    vector<int> coin = {2, 3, 5, 7};
    int target = 100;

    // vector<int> dp(target + 1, -1);
    // cout << permu_infini_tab(target, coin, dp) << endl;
    // display(dp);

    vector<int> dp(target + 1, 0);
    cout << combi_infini_tab(target, coin, dp) << endl;
    display(dp);
}

int rob_(int si, int ei, vector<int> &nums, vector<int> &dp)
{
    if (si == ei)
        return dp[si] = nums[si];

    if (dp[si] != -1)
        return dp[si];

    int first = (si + 2 <= ei ? rob_(si + 2, ei, nums, dp) : 0) + nums[si];
    int second = (si + 3 <= ei ? rob_(si + 3, ei, nums, dp) : 0) + nums[si + 1];

    return dp[si] = max(first, second);
}

int rob(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return nums[0];
    if (n == 2)
        return max(nums[0], nums[1]);

    vector<int> dp1(n, -1);
    vector<int> dp2(n, -1);
    int a = rob_(0, n - 2, nums, dp1);
    int b = rob_(1, n - 1, nums, dp2);
    return max(a, b);
    // int a = rob_(0, n - 1, nums, dp1);
    // display(dp1);
    // return a;
}

void lc213()
{
    vector<int> nums = {2, 7, 9, 3, 1};
    cout << rob(nums);
}

int lc718()
{
    //longest common subarray betweeen two arrays:==========================
    class Solution
    {
    public:
        int find(vector<int> &A, vector<int> &B, int i, int j, vector<vector<int>> &dp, int l1, int l2)
        {
            int max_ = 0;
            for (int i = l1; i >= 0; i--)
            {
                for (int j = l2; j >= 0; j--)
                {
                    if (i == l1 || j == l2 || A[i] != B[j])
                    {
                        dp[i][j] = 0;
                        continue;
                    }

                    int val = 1 + dp[i + 1][j + 1];
                    max_ = max(max_, val);
                    dp[i][j] = val;
                }
            }
            return max_;
        }
        int findLength(vector<int> &A, vector<int> &B)
        {
            int l1 = A.size();
            if (l1 == 0)
                return 0;
            int l2 = B.size();
            if (l2 == 0)
                return 0;

            vector<vector<int>> dp(l1 + 1, vector<int>(l2 + 1, -1));
            return find(A, B, 0, 0, dp, l1, l2);
        }
    };
}

void solve()
{
    // substr_subseq();
    // coin_change();
    // lc213();
    lc718();
}

int main()
{
    solve();
}
