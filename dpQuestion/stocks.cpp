#include <iostream>
#include <vector>
#include <cmath>

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


//memoization
int find(int idx, vector<int> &a, int f, int buy, vector<vector<int>> &dp)
{
    if (idx == a.size())
    {
        return dp[idx][buy] = 0;
    }

    if (dp[idx][buy] != -1)
    {
        return dp[idx][buy];
    }

    int pro = (int)-1e9;
    //i have already bought a share
    //first choice:: sell the current stock here(return the current sell price-fees + recursive call for forward)
    //second choice::dont sell now, call recursion forward

    if (buy == 1)
    {
        pro = max((a[idx] - f) + find(idx + 1, a, f, (buy + 1) % 2, dp), find(idx + 1, a, f, buy, dp));
    }

    //no stock bought now
    //first choice:: buy a stock now and call recursive
    //second choice:: do not buy a stock now and call recursive
    else
    {
        pro = max((-a[idx]) + find(idx + 1, a, f, (buy + 1) % 2, dp), find(idx + 1, a, f, buy, dp));
    }

    return dp[idx][buy] = pro;
}

//tabulation
int find2(vector<int> &a, int f, vector<vector<int>> &dp)
{
    for (int idx = a.size(); idx >= 0; idx--)
    {
        if (idx == a.size())
        {
            dp[idx][0] = 0;
            dp[idx][1] = 0;
            continue;
        }

        //no stock bought now
        //first choice:: buy a stock now and call recursive with buy=1 because we have bought now
        //second choice:: do not buy a stock now and call recursive with buy=0
        dp[idx][0] = max((-a[idx]) + dp[idx + 1][1], dp[idx + 1][0]);

        //i have already bought a share
        //first choice:: sell the current stock here(return the current sell price-fees + recursive call with buy=0 as net buying now for forward)
        //second choice::dont sell now, call recursion forward for
        dp[idx][1] = max((a[idx] - f) + dp[idx + 1][0], dp[idx + 1][1]);
    }

    //answer at index 0 and previous buying is zero
    return dp[0][0];
}

int maxProfit(vector<int> &a, int f)
{
    int n = a.size();
    if (n == 0)
        return 0;

    vector<vector<int>> dp(n + 1, vector<int>(2, -1));
    // find(int idx, vector<int> &a, int f, int buy, vector<vector<int>> &dp)
    // int ans = find(0, a, f, 0, dp);
    int ans = find2(a, f, dp);
    display2D(dp);
    return ans;
}

void solve()
{
    vector<int> a = {1, 3, 2, 8, 4, 9};
    int fee = 2;
    cout << maxProfit(a, fee);
}

int main()
{
    solve();
    return 0;
}