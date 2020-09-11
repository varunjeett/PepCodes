#include <iostream>
#include <vector>
#include <climits>

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

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode()
    {
        this->val = 0;
        this->left = nullptr;
        this->right = nullptr;
    }

    TreeNode(int ele)
    {
        this->val = ele;
        this->left = nullptr;
        this->right = nullptr;
    }
};

//matrix chain multiplication.==================================================

int MCM_recur(int si, int ei, vector<int> &cost)
{
    if (si + 1 == ei)
    {
        return 0;
    }

    int min_ = -1;
    for (int cut = si + 1; cut <= ei - 1; cut++)
    {
        int solve_left = MCM_recur(si, cut, cost);
        int solve_right = MCM_recur(cut, ei, cost);
        int solve_root = cost[si] * cost[cut] * cost[ei];
        min_ = min(min_, (solve_left + solve_right + solve_root));
    }
    return min_;
}

int MCM_memo(int si, int ei, vector<int> &cost, vector<vector<int>> &dp)
{
    if (si + 1 == ei) //only one matrix
    {
        return dp[si][ei] = 0;
    }

    if (dp[si][ei] != -1)
        return dp[si][ei];

    int min_ = INT_MAX;
    for (int cut = si + 1; cut < ei; cut++)
    {
        int solve_left = MCM_memo(si, cut, cost, dp);
        int solve_right = MCM_memo(cut, ei, cost, dp);

        int solve_root = cost[si] * cost[cut] * cost[ei]; //own operations
        solve_root += solve_left + solve_right;           //child operations

        min_ = min(min_, solve_root);
    }

    return dp[si][ei] = min_;
}

int MCM_tab(vector<int> &cost)
{
    int n = cost.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    for (int gap = 1; gap < n; gap++)
    {
        for (int si = 0, ei = gap; ei < n; si++, ei++)
        {
            if (si + 1 == ei) //only one matrix
            {
                dp[si][ei] = 0;
                continue;
            }

            int min_ = 1e8;
            for (int cut = si + 1; cut < ei; cut++)
            {
                int solve_left = dp[si][cut];
                int solve_right = dp[cut][ei];

                int solve_root = cost[si] * cost[cut] * cost[ei]; //own operations
                solve_root += solve_left + solve_right;           //child operations

                min_ = min(min_, solve_root);
            }

            dp[si][ei] = min_;
        }
    }
    display2D(dp);
    return dp[0][n - 1];
}

int MCM_tab_string(vector<int> &cost)
{
    int n = cost.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<string>> dp_ans(n, vector<string>(n, ""));

    for (int gap = 1; gap < n; gap++)
    {
        for (int si = 0, ei = gap; ei < n; si++, ei++)
        {
            if (gap == 1) //single matrix
            {
                dp[si][ei] = 0;
                dp_ans[si][ei] = (char)(si + 'A');
                continue;
            }

            int min_ = 1e9;
            int finalCut = -1;

            for (int cut = si + 1; cut <= ei - 1; cut++)
            {
                int solve_left = dp[si][cut];
                int solve_right = dp[cut][ei];
                int solve_root = cost[si] * cost[cut] * cost[ei];
                solve_root += solve_left + solve_right;

                if (solve_root < min_) //storing the minimum
                {
                    min_ = solve_root;
                    finalCut = cut;
                }
            }

            dp[si][ei] = min_;
            dp_ans[si][ei] = '(' + dp_ans[si][finalCut] + dp_ans[finalCut][ei] + ')';
        }
    }

    cout << dp[0][n - 1] << endl;
    cout << dp_ans[0][n - 1] << endl;
    return 0;
}

void MCM()
{
    vector<int> cost = {2, 3, 4, 5, 6, 7};
    int n = cost.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    // cout << MCM_recur(0, n - 1, cost) << endl;
    // cout << MCM_memo(0, n - 1, cost, dp) << endl;
    // display2D(dp);
    // cout << MCM_tab(cost) << endl;
    MCM_tab_string(cost);
}

//optimal bst.================================================

// vector<int> keys = {10, 20, 30, 40, 50};
// vector<int> fre = {3, 5, 2, 7, 4};

int findCost(int si, int ei, vector<int> &fre)
{
    int sum = 0;
    for (int i = si; i <= ei; i++)
    {
        sum += fre[i];
    }
    return sum;
}

int oBST_recur(int si, int ei, vector<int> &fre)
{
    if (si > ei)
        return 0;

    int min_ = 1e9;
    for (int root = si; root <= ei; root++)
    {
        int solve_left = oBST_recur(si, root - 1, fre);
        int solve_right = oBST_recur(root + 1, ei, fre);

        // int solve_root=2*solve_left+fre[cost]+2*solve_right; is wrong as height gets more than  2..
        int solve_root = solve_left + findCost(si, ei, fre) + solve_right;
        min_ = min(min_, solve_root);
    }
    return min_;
}

int oBST_memo(int si, int ei, vector<int> &fre, vector<vector<int>> &dp)
{
    if (dp[si][ei] != -1)
    {
        return dp[si][ei];
    }

    int min_ = INT_MAX;
    for (int cut = si; cut <= ei; cut++)
    {
        int solve_left = (si == cut) ? 0 : oBST_memo(si, cut - 1, fre, dp);
        int solve_right = (ei == cut) ? 0 : oBST_memo(cut + 1, ei, fre, dp);

        int total_cost = solve_left + findCost(si, ei, fre) + solve_right;
        min_ = min(min_, total_cost);
    }
    return dp[si][ei] = min_;
}

int oBST_tab(vector<int> &fre)
{
    int n = fre.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));

    for (int gap = 0; gap < n; gap++)
    {
        for (int si = 0, ei = gap; ei < n; si++, ei++)
        {
            int min_ = INT_MAX;
            for (int cut = si; cut <= ei; cut++)
            {
                int solve_left = (si == cut) ? 0 : dp[si][cut - 1];
                int solve_right = (ei == cut) ? 0 : dp[cut + 1][ei];

                int total_cost = solve_left + findCost(si, ei, fre) + solve_right;
                min_ = min(min_, total_cost);
            }

            dp[si][ei] = min_;
        }
    }

    display2D(dp);
    return dp[0][n - 1];
}

void oBST()
{
    vector<int> keys = {10, 20, 30, 40, 50};
    vector<int> fre = {3, 5, 2, 7, 4};
    int n = keys.size();
    cout << oBST_recur(0, n - 1, fre);
    // vector<vector<int>> dp(n, vector<int>(n, -1));
    // cout << oBST_memo(0, n - 1, fre, dp) << endl;
    // display2D(dp);
    // cout << oBST_tab(fre);
}

int maxCoins_recur(vector<int> &nums, int si, int ei, int n)
{
    int lVal = (si == 0) ? 1 : nums[si - 1];
    int rVal = (ei == n - 1) ? 1 : nums[ei + 1];

    int max_ = 0;
    for (int cut = si; cut <= ei; cut++)
    {
        int solve_left = (cut == si) ? 0 : maxCoins_recur(nums, si, cut - 1, n);
        int solve_right = (cut == ei) ? 0 : maxCoins_recur(nums, cut + 1, ei, n);

        int solve_root = solve_left + (lVal * nums[cut] * rVal) + solve_right;

        max_ = max(max_, solve_root);
    }

    return max_;
}

int maxCoins_memo(vector<int> &nums, int si, int ei, int n, vector<vector<int>> &dp)
{
    if (dp[si][ei] != -1)
    {
        return dp[si][ei];
    }

    int lVal = (si == 0) ? 1 : nums[si - 1];
    int rVal = (ei == n - 1) ? 1 : nums[ei + 1];

    int max_ = 0;
    for (int cut = si; cut <= ei; cut++)
    {
        int solve_left = (cut == si) ? 0 : maxCoins_memo(nums, si, cut - 1, n, dp);
        int solve_right = (cut == ei) ? 0 : maxCoins_memo(nums, cut + 1, ei, n, dp);

        int solve_root = solve_left + (lVal * nums[cut] * rVal) + solve_right;

        max_ = max(max_, solve_root);
    }

    return dp[si][ei] = max_;
}

int maxCoins_tab(vector<int> &nums)
{
    int n = nums.size();

    if (n == 0)
        return 0;
    if (n == 1)
        return nums[0];

    vector<vector<int>> dp(n, vector<int>(n, -1));

    for (int gap = 0; gap < n; gap++)
    {
        for (int si = 0, ei = gap; ei < n; si++, ei++)
        {
            int lVal = (si == 0) ? 1 : nums[si - 1];     //3
            int rVal = (ei == n - 1) ? 1 : nums[ei + 1]; //8

            int max_ = 0;
            for (int cut = si; cut <= ei; cut++)
            {
                int solve_left = (cut == si) ? 0 : dp[si][cut - 1];
                int solve_right = (cut == ei) ? 0 : dp[cut + 1][ei];

                int solve_root = solve_left + (lVal * nums[cut] * rVal) + solve_right;

                max_ = max(max_, solve_root);
            }

            dp[si][ei] = max_;
        }
    }
    display2D(dp);
    return dp[0][n - 1];
}

int maxCoins(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return nums[0];
    // return maxCoins_recur(nums, 0, n - 1, n);
    // vector<vector<int>> dp(n, vector<int>(n, -1));
    // int ans = maxCoins_memo(nums, 0, n - 1, n, dp);
    // display2D(dp);
    return maxCoins_tab(nums);
}

void lc312()
{
    vector<int> nums = {3, 5};
    cout << maxCoins(nums);
}

bool isInterleave(int i, int j, int k, string &s1, string &s2, string &s3, int len1, int len2, int len3)
{
    if (i == len1 || j == len2)
    {
        if (i == len1)
        {
            return (s2.substr(j) == s3.substr(k)) ? true : false;
        }
        else
        {
            return (s1.substr(i) == s3.substr(k)) ? true : false;
        }
    }

    bool res = false;
    if (s1[i] == s3[k] || s2[j] == s3[k])
    {
        if (s1[i] == s2[j])
        {
            res = isInterleave(i + 1, j, k + 1, s1, s2, s3, len1, len2, len3) || isInterleave(i, j + 1, k + 1, s1, s2, s3, len1, len2, len3);
        }
        else
        {
            res = (s1[i] == s3[k]) ? isInterleave(i + 1, j, k + 1, s1, s2, s3, len1, len2, len3) : isInterleave(i, j + 1, k + 1, s1, s2, s3, len1, len2, len3);
        }
    }
    return res;
}

bool isInterleave(string s1, string s2, string s3)
{
    int len1 = s1.length();
    int len2 = s2.length();
    int len3 = s3.length();
    if (len1 + len2 != len3)
        return false;
    return isInterleave(0, 0, 0, s1, s2, s3, len1, len2, len3);
}

void lc97()
{
    cout << (boolalpha) << isInterleave("aabcc", "dbbca", "aadbbbaccc");
}

void solve()
{
    // MCM();
    oBST();
    // lc312();
    // lc97();
}

int findWays(int si, int ei, vector<int> &arr, vector<vector<int>> &dp)
{

    if ((ei - si + 1 ) < 3)
    {
        return dp[si][ei] = 0;
    }

    if (dp[si][ei] != -1)
    {
        return dp[si][ei];
    }

    int min_ = 1e9;
    for (int cut = si + 1; cut <= ei-1; cut++)
    {
        int solve_left=findWays(si, cut, arr, dp);
        int solve_right=findWays(cut, ei, arr, dp);

        int solve_root=(arr[si] * arr[cut] * arr[ei]);
        solve_root+=solve_left+solve_right;
        cout<<solve_root<<"@"<<cut<<endl;
        min_ = min(solve_root, min_);
    }

    return dp[si][ei] = min_;
}

int minScoreTriangulation(vector<int> &A)
{
    int n = A.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return findWays(0, n - 1, A, dp);
}

int main()
{
    // solve();

    vector<int> arr{1, 2,3,4};
    cout << minScoreTriangulation(arr);
}
