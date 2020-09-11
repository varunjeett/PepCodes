#include <iostream>
#include <vector>
#include <math.h>

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

int minPath_memo(int sr, int sc, int er, int ec, vector<vector<int>> &grid, vector<vector<int>> &dp)
{

    if (er == sr && sc == ec)
        return dp[sr][sc] = grid[sr][sc];

    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    int ans = +1e8;

    if (sr + 1 <= er)
        ans = min(ans, minPath_memo(sr + 1, sc, er, ec, grid, dp));
    if (sc + 1 <= ec)
        ans = min(ans, minPath_memo(sr, sc + 1, er, ec, grid, dp));

    return dp[sr][sc] = (ans + grid[sr][sc]);
}

int minPath_tab(int sr, int sc, int er, int ec, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    for (sr = er; sr >= 0; sr--)
    {
        for (sc = ec; sc >= 0; sc--)
        {
            if (er == sr && sc == ec)
            {
                dp[sr][sc] = grid[sr][sc];
                continue;
            }

            int ans = +1e8;

            if (sr + 1 <= er)
                ans = min(ans, dp[sr + 1][sc]);
            if (sc + 1 <= ec)
                ans = min(ans, dp[sr][sc + 1]);

            dp[sr][sc] = (ans + grid[sr][sc]);
        }
    }

    return dp[0][0];
}

void minPath()
{
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    vector<vector<int>> dp(3, vector<int>(3, 0));
    // cout << minPath_memo(0, 0, 2, 2, grid, dp);
    cout << minPath_tab(0, 0, 2, 2, grid, dp);

    cout << endl;
    display2D(dp);
}

int goldmine_memo(int sr, int sc, int er, int ec, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    if (sc == ec)
        return dp[sr][sc] = grid[sr][sc];

    if (dp[sr][sc] != -1)
        return dp[sr][sc];

    int ans = -1e8;
    if (sr - 1 >= 0 && sc + 1 <= ec)
    {
        ans = max(ans, goldmine_memo(sr - 1, sc + 1, er, ec, grid, dp));
    }
    if (sc + 1 <= ec)
    {
        ans = max(ans, goldmine_memo(sr, sc + 1, er, ec, grid, dp));
    }
    if (sr + 1 <= er && sc + 1 <= ec)
    {
        ans = max(ans, goldmine_memo(sr + 1, sc + 1, er, ec, grid, dp));
    }
    return dp[sr][sc] = ans + grid[sr][sc];
}

int goldmine_tab(int sr, int sc, int er, int ec, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    for (sc = ec; sc >= 0; sc--)
    {
        for (sr = 0; sr <= er; sr++)
        {
            if (sc == ec)
            {
                dp[sr][sc] = grid[sr][sc];
                continue;
            }

            int ans = -1e8;
            if (sr - 1 >= 0 && sc + 1 <= ec)
            {
                ans = max(ans, dp[sr - 1][sc + 1]);
            }
            if (sc + 1 <= ec)
            {
                ans = max(ans, dp[sr][sc + 1]);
            }
            if (sr + 1 <= er && sc + 1 <= ec)
            {
                ans = max(ans, dp[sr + 1][sc + 1]);
            }

            dp[sr][sc] = ans + grid[sr][sc];
        }
    }
    return 0;
}

void goldmine()
{
    vector<vector<int>> grid = {{1, 3, 1, 5},
                                {2, 2, 4, 1},
                                {5, 0, 2, 3},
                                {0, 6, 1, 2}};

    vector<vector<int>> dp(4, vector<int>(4, -1));
    // int max_ = 0;
    // for (int i = 0; i < grid.size(); i++)
    // {
    //     max_ = max(max_, goldmine_memo(i, 0, 3, 3, grid,dp));
    // }
    // cout << max_ << endl;

    goldmine_tab(0, 0, 3, 3, grid, dp);
    display2D(dp);

    int max_ = 0;
    for (int i = 0; i < dp.size(); i++)
    {
        max_ = max(max_, dp[i][0]);
    }
    cout << max_ << endl;
}

int friendPair_recur(int n)
{
    if (n <= 1)
        return 1;

    int alone = friendPair_recur(n - 1);
    int group = friendPair_recur(n - 2) * (n - 1);

    return alone + group;   //use modulo here
}

int friendPair_memo(int n, vector<int> &dp)
{
    if (n <= 1)
        return dp[n] = 1;

    int alone = friendPair_memo(n - 1, dp);
    int group = friendPair_memo(n - 2, dp) * (n - 1);

    return dp[n] = alone + group;
}

int friendPair_tab(int n, vector<int> &dp)
{
    if (n <= 2) //base case need no iteration
        return n;

    int N = n;
    for (n = 0; n <= N; n++)
    {
        if (n <= 1)
        {
            dp[n] = 1;
            continue;
        }
        dp[n] = (dp[n - 1] + (dp[n - 2] * (n - 1))) % (int)(1e9);
    }
    return dp[N];
}

int friendPair_twoPointer(int n)
{
    if (n <= 2) //base case need no iteration
        return n;

    int N = n;
    long long a = 1; //for dp[n-2]
    long long b = 1; //for dp[n-1]
    long long sum = 0;
    for (n = 2; n <= N; n++)
    {
        sum = ((a * (n - 1)) + b) % (int)(pow(10, 9) + 7); //for greater numbers
        a = b;
        b = sum;
    }
    return sum;
}

void friendPair()
{
    int n = 1000000;
    // vector<int> dp(n + 1, 0);
    // cout << friendPair_tab(n, dp);
    // display(dp);
    cout << friendPair_twoPointer(n);
}

int nPeopleKGroup_recur(int n, int k)
{
    if (k == 1 || n == k)
    {
        return 1;
    }

    int seperate = nPeopleKGroup_recur(n - 1, k - 1);
    int together = nPeopleKGroup_recur(n - 1, k) * k;

    return seperate + together;
}

int nPeopleKGroup_memo(int n, int k, vector<vector<int>> &dp)
{
    if (k == 1 || n == k)
    {
        return dp[k][n] = 1;
    }

    if (dp[k][n] != 0)
    {
        return dp[k][n];
    }

    int seperate = nPeopleKGroup_memo(n - 1, k - 1, dp);
    int together = nPeopleKGroup_memo(n - 1, k, dp) * k;

    return dp[k][n] = seperate + together;
}

int nPeopleKGroup_tab(int N, int K, vector<vector<int>> &dp)
{
    for (int k = 0; k <= K; k++)
    {
        for (int n = 0; n <= N; n++)
        {
            if (k == 0 || n < k)
            {
                continue;
            }

            if (k == 1 || n == k)
            {
                dp[k][n] = 1;
                continue;
            }

            int seperate = dp[k - 1][n - 1];
            int together = dp[k][n - 1] * k;

            dp[k][n] = seperate + together;
        }
    }

    return dp[K][N];
}

void nPeopleKGroup()
{
    int n = 5;
    int k = 3;
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
    //cout << nPeopleKGroup_recur(n, k) << endl;
    //cout << nPeopleKGroup_memo(n, k, dp) << endl;
    cout << nPeopleKGroup_tab(n, k, dp) << endl;
    display2D(dp);
}

int findPath(int sr, int sc, int er, int ec, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
        return dp[sr][sc] = 1;
    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    int right = 0;
    int down = 0;

    if (sc + 1 <= ec && grid[sr][sc + 1] != 1)
        right = findPath(sr, sc + 1, er, ec, grid, dp);
    if (sr + 1 <= er && grid[sr + 1][sc] != 1)
        down = findPath(sr + 1, sc, er, ec, grid, dp);

    return dp[sr][sc] = right + down;
}

int uniquePathsWithObstacles_memo(vector<vector<int>> &grid)
{
    int n = grid.size();
    if (n == 0)
        return 0;
    int m = grid[0].size();
    if (m == 0)
        return 0;

    if (grid[0][0] == 1 || grid[n - 1][m - 1] == 1)
        return 0;

    vector<vector<int>> dp(n, vector<int>(m, 0));

    int ans = findPath(0, 0, n - 1, m - 1, grid, dp);
    display2D(dp);
    return ans;
}

int uniquePathsWithObstacles_tab(vector<vector<int>> &grid) //tabulation
{
    int n = grid.size();
    if (n == 0)
        return 0;
    int m = grid[0].size();
    if (m == 0)
        return 0;

    if (grid[0][0] == 1 || grid[n - 1][m - 1] == 1)
        return 0;

    vector<vector<int>> dp(n, vector<int>(m, 0));

    int sr = 0;
    int sc = 0;
    int er = n - 1;
    int ec = m - 1;

    for (int sr = er; sr >= 0; sr--)
    {
        for (int sc = ec; sc >= 0; sc--)
        {
            if (grid[sr][sc] == 1)
                continue;

            if (sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }

            int right = 0;
            int down = 0;

            if (sc + 1 <= ec)
                right = dp[sr][sc + 1];
            if (sr + 1 <= er)
                down = dp[sr + 1][sc];

            dp[sr][sc] = right + down;
        }
    }

    display2D(dp);
    return dp[0][0];
}

//lc 120.======================================================
int findMin(int sr, int sc, int er, vector<vector<int>> &tri, vector<vector<int>> &dp)
{
    for (sr = er; sr >= 0; sr--)
    {
        for (sc = 0; sc <= sr; sc++)
        {
            if (sr == er)
            {
                dp[sr][sc] = tri[sr][sc];
                continue;
            }

            int down = dp[sr + 1][sc];
            int down_right = dp[sr + 1][sc + 1];

            dp[sr][sc] = min(down, down_right) + tri[sr][sc];
        }
    }
    return dp[0][0];
}

int minimumTotal(vector<vector<int>> &tri)
{
    int n = tri.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return tri[0][0];

    vector<vector<int>> dp(n, vector<int>(n, -1));
    return findMin(0, 0, n - 1, tri, dp);
}

int minimumTotal_best(vector<vector<int>> &tri)
{
    int n = tri.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return tri[0][0];

    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            tri[i][j] += min(tri[i + 1][j], tri[i + 1][j + 1]);
        }
    }

    return tri[0][0];
}

void lc120()
{
    vector<vector<int>> tri = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    cout << minimumTotal(tri) << endl;
    cout << minimumTotal_best(tri);
}

//lc 198.======================================================
int robHouse(int st, int N, vector<int> &nums, vector<int> &dp)
{
    if (st == N)
        return dp[st] = nums[N];
    if (dp[st] != -1)
        return dp[st];

    int first = nums[st] + (st + 2 <= N) ? robHouse(st + 2, N, nums, dp) : 0;
    int second = nums[st + 1] + (st + 3 <= N) ? robHouse(st + 3, N, nums, dp) : 0;

    return dp[st] = max(first, second);
}

int robHouse_tab(int st, int N, vector<int> &nums, vector<int> &dp)
{
    for (int st = N; st >= 0; st--)
    {
        if (st == N)
        {
            dp[st] = nums[N];
            continue;
        }

        int first = nums[st] + (st + 2 <= N) ? dp[st + 2] : 0;
        int second = nums[st + 1] + (st + 3 <= N) ? dp[st + 3] : 0;

        dp[st] = max(first, second);
    }
    return dp[0];
}

int rob(vector<int> &nums)
{
    if (nums.size() == 0)
        return 0;
    if (nums.size() == 1)
        return nums[0];
    if (nums.size() == 2)
        return max(nums[0], nums[1]);
    vector<int> dp(nums.size(), -1);
    int ans = robHouse(0, nums.size() - 1, nums, dp);
    display(dp);
    return ans;
}

void extra()
{
    // vector<vector<int>> grid = {
    //     {0, 0, 0},
    //     {0, 1, 0},
    //     {0, 0, 0}};

    // cout << uniquePathsWithObstacles_tab(grid);

    //lc120();
    vector<int> nums{2, 7, 9, 3, 1};
    cout << rob(nums);
}

void solve()
{
    //minPath();
    //goldmine();
    //friendPair();
    //nPeopleKGroup();
    extra();
}

int main()
{
    solve();
}
