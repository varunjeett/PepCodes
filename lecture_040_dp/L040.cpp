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

//plain recursive
int fibo_01(int N)
{
    if (N <= 1)
        return N;
    return fibo_01(N - 1) + fibo_01(N - 2);
}

int fibo_memo(int N, vector<int> &dp)
{
    if (N <= 1)
        return dp[N] = N; //base case

    if (dp[N] != 0)
        return dp[N]; //use the memoized value first

    return dp[N] = fibo_memo(N - 1, dp) + fibo_memo(N - 2, dp);
}

int fibo_tab(int N, vector<int> &dp)
{
    int n = N;
    for (N = 0; N <= n; N++)
    {
        if (N <= 1)
        {
            dp[N] = N; //base case
            continue;
        }

        dp[N] = dp[N - 1] + dp[N - 2];
    }
    return dp[n];
}

int fibo_best(int N)
{
    if (N <= 1)
        return N;
    int a = 0;
    int b = 1;
    int sum;
    for (int n = 2; n <= N; n++)
    {
        sum = a + b;
        a = b;
        b = sum;
    }
    return sum;
}

void fibo()
{
    int n = 0;
    vector<int> dp(n + 1, 0);
    // cout<<fibo_01(n);  //we need 8th term of sequence , so we'll pass n-1
    //  cout<<fibo_memo(n, dp);
    // cout<<fibo_tab(n , dp)<<endl;
    cout << fibo_best(n);
    // display(dp);
}

int mazepath_01(int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
    {
        return 1; //signify a path is found
    }

    int count = 0;

    if (sr + 1 <= er) //down
    {
        count += mazepath_01(sr + 1, sc, er, ec);
    }
    if (sc + 1 <= ec) //right
    {
        count += mazepath_01(sr, sc + 1, er, ec);
    }
    if (sr + 1 <= er && sc + 1 <= ec) //diagonal
    {
        count += mazepath_01(sr + 1, sc + 1, er, ec);
    }
    return count;
}

int mazepath_memo(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
    {
        return dp[sr][sc] = 1;
    }

    if (dp[sr][sc] != 0)
    {
        return dp[sr][sc];
    }

    int count = 0;
    if (sr + 1 <= er) //down
    {
        count += mazepath_memo(sr + 1, sc, er, ec, dp);
    }
    if (sc + 1 <= ec) //right
    {
        count += mazepath_memo(sr, sc + 1, er, ec, dp);
    }
    if (sr + 1 <= er && sc + 1 <= ec) //vertical
    {
        count += mazepath_memo(sr + 1, sc + 1, er, ec, dp);
    }
    return dp[sr][sc] = count;
}

int mazepath_tab(int er, int ec, vector<vector<int>> &dp)
{
    for (int sr = er; sr >= 0; sr--)
    {
        for (int sc = ec; sc >= 0; sc--)
        {
            if (sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }

            int count = 0;
            if (sr + 1 <= er) //down
            {
                count += dp[sr + 1][sc];
            }
            if (sc + 1 <= ec) //right
            {
                count += dp[sr][sc + 1];
            }
            if (sr + 1 <= er && sc + 1 <= ec) //vertical
            {
                count += dp[sr + 1][sc + 1];
            }
            dp[sr][sc] = count;
        }
    }
    return dp[0][0];
}

int mazepath_jump_01(int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
    {
        return 1;
    }

    int jump = 1;
    int count = 0;

    for (jump = 1; sr + jump <= er; jump++) // down jump
    {
        count += mazepath_jump_01(sr + jump, sc, er, ec);
    }
    for (jump = 1; sc + jump <= ec; jump++) // right jump
    {
        count += mazepath_jump_01(sr, sc + jump, er, ec);
    }
    for (jump = 1; sr + jump <= er && sc + jump <= ec; jump++) // diagonal jump
    {
        count += mazepath_jump_01(sr + jump, sc + jump, er, ec);
    }
    return count;
}

int mazepath_jump_memo(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
    {
        return dp[sr][sc] = 1;
    }

    if (dp[sr][sc] != 0)
    {
        return dp[sr][sc];
    }

    int jump = 1;
    int count = 0;

    for (jump = 1; sr + jump <= er; jump++)
    {
        count += mazepath_jump_memo(sr + jump, sc, er, ec, dp);
    }
    for (jump = 1; sc + jump <= ec; jump++)
    {
        count += mazepath_jump_memo(sr, sc + jump, er, ec, dp);
    }
    for (jump = 1; sr + jump <= er && sc + jump <= ec; jump++)
    {
        count += mazepath_jump_memo(sr + jump, sc + jump, er, ec, dp);
    }
    return dp[sr][sc] = count;
}

void mazepath()
{
    int n = 3;
    int m = 3;
    vector<vector<int>> dp(n, vector<int>(m, 0));
    // cout<<mazepath_01(0,0,n-1,m-1);
    //cout << mazepath_memo(0, 0, n - 1, m - 1, dp)<< endl;
    // cout << mazepath_tab(n - 1, m - 1, dp) << endl;
    //  display2D(dp);
    //cout << mazepath_jump_01(0, 0, n - 1, m - 1);
    cout << mazepath_jump_memo(0, 0, n - 1, m - 1, dp) << endl;
    display2D(dp);
}

int boardpath_recur(int st, int ed)
{
    if (st == ed)
        return 1;

    int count = 0;
    for (int dice = 1; dice <= 6 && dice + st <= ed; dice++)
    {
        count += boardpath_recur(st + dice, ed);
    }
    return count;
}

int boardpath_memo(int st, int ed, vector<int> &dp)
{
    if (st == ed)
        return dp[st] = 1;

    if (dp[st] != 0)
        return dp[st];

    int count = 0;
    for (int dice = 1; dice <= 6 && dice + st <= ed; dice++)
    {
        count += boardpath_memo(st + dice, ed, dp);
    }
    return dp[st] = count;
}

int boardpath_tab(int st, int ed, vector<int> &dp)
{
    int ST = st;
    for (st = ed; st >= ST; st--)
    {
        if (st == ed)
        {
            dp[st] = 1;
            continue;
        }
        int count = 0;
        for (int dice = 1; dice <= 6 && dice + st <= ed; dice++)
        {
            count += dp[st + dice];
        }
        dp[st] = count;
    }
    return dp[ST];
}

void boardpath()
{
    int st = 4;
    int ed = 10;
    vector<int> dp(ed + 1, 0);
    // cout << boardpath_recur(st, ed)<<endl;
    // cout << boardpath_memo(st, ed, dp) << endl;
    cout << boardpath_tab(st, ed, dp) << endl;
    display(dp);
}

int findCost_memo(int n, vector<int> &cost, vector<int> &dp)
{
    if (n <= 1)
        return dp[n] = cost[n];

    if (dp[n] != 0)
        return dp[n];

    return dp[n] = min(findCost_memo(n - 1, cost, dp), findCost_memo(n - 2, cost, dp)) + cost[n];
}

int minCostClimbingStairs_memo(vector<int> &cost)
{
    int n = cost.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return cost[0];

    cost.push_back(0);
    vector<int> dp(n + 1, 0);
    return findCost_memo(n, cost, dp);
}

int findCostminCostStair_tab(int n, vector<int> &cost, vector<int> &dp)
{

    int N = n;
    for (n = 0; n <= N; n++)
    {
        if (n <= 1)
        {
            dp[n] = cost[n];
            continue;
        }
        dp[n] = min(dp[n - 1], dp[n - 2]) + cost[n];
    }

    return dp[N];
}

int minCostClimbingStairs_tab(vector<int> &cost)
{
    int n = cost.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return cost[0];

    cost.push_back(0);
    vector<int> dp(n + 1, 0);
    int ans = findCost_tab(n, cost, dp);
    for (int ele : dp)
    {
        cout << ele << ",";
    }
    return ans;
}

int minCostClimbingStairs_twoPointer(vector<int> &cost)
{
    int n = cost.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return cost[0];

    cost.push_back(0);

    int a = cost[0];
    int b = cost[1];
    int sum = 0;
    for (int i = 2; i < (n + 1); i++)
    {
        sum = min(a, b) + cost[i];
        a = b;
        b = sum;
    }
    return sum;
}

void minCostStair()
{
    vector<int> stair = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    cout << minCostClimbingStairs_twoPointer(stair);
}

void solve()
{
    // fibo();
    // mazepath();
    // boardpath();
    minCostStair(); //leetcode 746
}

int main()
{
    solve();
    return 0;
}

