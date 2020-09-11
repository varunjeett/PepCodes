#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <unordered_map>

using namespace std;

class TreeNode
{
public:
    int val = 0;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    TreeNode(int ele)
    {
        this->val = ele;
    }
};

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

//triangulation memo.==============================================
int findWays(int si, int ei, vector<int> &arr, vector<vector<int>> &dp)
{
    if ((ei - si + 1) < 3)
    {
        return dp[si][ei] = 0;
    }

    if (dp[si][ei] != -1)
    {
        return dp[si][ei];
    }

    int min_ = 1e9;
    for (int cut = si + 1; cut <= ei - 1; cut++)
    {
        int solve_left = findWays(si, cut, arr, dp);
        int solve_right = findWays(cut, ei, arr, dp);

        int solve_root = (arr[si] * arr[cut] * arr[ei]);
        solve_root += solve_left + solve_right;
        min_ = min(solve_root, min_);
    }

    return dp[si][ei] = min_;
}

//dp
int findWays_dp(vector<int> &arr)
{
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));

    for (int gap = 1; gap < n; gap++)
    {
        for (int si = 0, ei = gap; ei < n; si++, ei++)
        {
            if ((ei - si + 1) < 3)
            {
                dp[si][ei] = 0;
                continue;
            }

            int min_ = 1e9;
            for (int cut = si + 1; cut <= ei - 1; cut++)
            {
                int solve_left = dp[si][cut];
                int solve_right = dp[cut][ei];

                int solve_root = (arr[si] * arr[cut] * arr[ei]);
                solve_root += solve_left + solve_right;
                min_ = min(solve_root, min_);
            }

            dp[si][ei] = min_;
        }
    }
    return dp[0][n - 1];
}

int minScoreTriangulation(vector<int> &A)
{
    int n = A.size();
    return findWays_dp(A);
    // vector<vector<int>> dp(n, vector<int>(n, -1));
    // return findWays(0, n - 1, A, dp);
}

void triangulation()
{
    //leetcode: 1039
    vector<int> arr = {2, 3, 4, 1, 5, 8};
    cout << minScoreTriangulation(arr);
}

int findWays(int si, int ei, vector<vector<int>> &dp)
{

    if (dp[si][ei] != -1)
    {
        return dp[si][ei];
    }

    int count = 0;
    for (int cut = si; cut <= ei; cut++)
    { //cut represents the root, we are giving chance to everyone to become root.
        int solve_left = (cut == si) ? 1 : findWays(si, cut - 1, dp);
        int solve_right = (cut == ei) ? 1 : findWays(cut + 1, ei, dp);

        count += solve_left * solve_right;
    }

    return dp[si][ei] = count;
}

int findWays_dp(int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

    for (int gap = 0; gap < n; gap++)
    {
        for (int si = 1, ei = gap + 1; ei <= n; si++, ei++)
        {
            int count = 0;

            for (int cut = si; cut <= ei; cut++)
            { //cut represents the root, we are giving chance to everyone to become root.
                int solve_left = (cut == si) ? 1 : dp[si][cut - 1];
                int solve_right = (cut == ei) ? 1 : dp[cut + 1][ei];

                count += solve_left * solve_right;
            }

            dp[si][ei] = count;
        }
    }

    return dp[1][n];
}

void bstPossible()
{
    int n = 19;

    // if we want to have base case.== follow below
    //indexing from 1 ,2,3,... n (for nodes values)
    //our base cases will go from si-1 to ei+1, so we need 0,1,2,3,4 for n=3;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    cout << findWays(1, n, dp) << endl;
    display2D(dp);

    cout << findWays_dp(n);
}

vector<TreeNode *> generate(int si, int ei)
{
    vector<TreeNode *> self;

    for (int cut = si; cut <= ei; cut++)
    {
        //cut represents the root, we are giving chance to everyone to become root.
        vector<TreeNode *> left_st = {nullptr};
        left_st = (cut == si) ? left_st : generate(si, cut - 1);

        vector<TreeNode *> right_st = {nullptr};

        right_st = (cut == ei) ? right_st : generate(cut + 1, ei);

        for (TreeNode *lc : left_st)
        {
            for (TreeNode *rc : right_st)
            {
                TreeNode *root = new TreeNode(cut);
                root->left = lc;
                root->right = rc;

                self.push_back(root);
            }
        }
    }

    return self;
}

//MEMOIZED WITH HASHMAP AND CREATING A CUSTOM FUNCTION FOR HASHMAP

// class Solution {
// public:

//     struct hash_pair {
//     template <class T1, class T2>
//     size_t operator()(const pair<T1, T2>& p) const
//     {
//         auto hash1 = hash<T1>{}(p.first);
//         auto hash2 = hash<T2>{}(p.second);
//         return hash1 ^ hash2;
//     }
//    };

//     unordered_map<pair<int, int>, vector<TreeNode*>, hash_pair> dp;

//     vector<TreeNode *> generate(int si, int ei)
//   {
//     if(dp.find({si,ei})!=dp.end())
//         return dp[{si,ei}];

//     vector<TreeNode *> self;
//     for (int cut = si; cut <= ei; cut++)
//     {
//         //cut represents the root, we are giving chance to everyone to become root.
//         vector<TreeNode *> left_st = {nullptr};
//         left_st = (cut == si) ? left_st : generate(si, cut - 1);

//         vector<TreeNode *> right_st = {nullptr};

//         right_st = (cut == ei) ? right_st : generate(cut+1,ei);

//         for (TreeNode *lc : left_st)
//         {
//             for (TreeNode *rc : right_st)
//             {
//                 TreeNode *root = new TreeNode(cut);
//                 root->left = lc;
//                 root->right = rc;

//                 self.push_back(root);
//             }
//         }
//     }

//     return dp[{si,ei}]=self;
//     }

//     vector<TreeNode*> generateTrees(int n) {
//         if(n==0)
//             return {};
//         else
//             return generate(1,n);
//     }
// };

void display_tree(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }

    string str = "";
    str += (root->left == nullptr ? "." : to_string(root->left->val));
    str += " <- " + to_string(root->val) + " -> ";
    str += (root->right == nullptr ? "." : to_string(root->right->val));

    cout << str << endl;

    display_tree(root->left);
    display_tree(root->right);

    return;
}

void createBst()
{
    int n = 3;
    vector<TreeNode *> ans = generate(1, n);
    for (TreeNode *r : ans)
    {
        display_tree(r);
        cout << endl;
    }
}

void solve()
{
    // triangulation();
    // bstPossible();
    createBst();
}

int main()
{
    solve();
}
