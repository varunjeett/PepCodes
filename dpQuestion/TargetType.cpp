#include <bits/stdc++.h>
using namespace std;

void display(vector<long> &arr)
{
    for (long ele : arr)
        cout << ele << " ";
    cout << endl;
}

void display2D(vector<vector<long>> &arr)
{
    for (vector<long> ar : arr)
        display(ar);
    cout << endl;
}

//memoization is faster for target sum type questions like this one
//48 ms
long find(int d, int f, int target, vector<vector<long>> &dp)
{

    if (d == 0)
    {
        if (target == 0)
            return dp[d][target] = 1;
        else
            return dp[d][target] = 0;
    }

    if (dp[d][target] != -1)
        return dp[d][target];

    long count = 0;
    for (int i = 1; i <= f; i++)
    {
        if ((target - i) >= 0)
            count = ((count % mod) + (find(d - 1, f, target - i, dp) % mod) % mod);
        else
            break;
    }

    return dp[d][target] = count;
}
//136 ms
long find2(int D, int f, int TARGET, vector<vector<long>> &dp)
{
    for (int d = 0; d <= D; d++)
    {
        for (int target = 0; target <= TARGET; target++)
        {
            if (d == 0)
            {
                if (target == 0)
                    dp[d][target] = 1;
                else
                    dp[d][target] = 0;

                continue;
            }

            long count = 0;
            for (int i = 1; i <= f; i++)
            {
                if ((target - i) >= 0)
                    count = ( (count % mod) + (dp[d - 1][target - i] % mod) % mod);
                else
                    break;
            }

            dp[d][target] = count;
        }
    }

    display2D(dp);
    return dp[D][TARGET];
}

int numRollsToTarget(int d, int f, int target)
{
    vector<vector<long>> dp(d + 1, vector<long>(target + 1, -1));
    long val = find2(d, f, target, dp);
    return (val % mod);
}

int main()
{
    cout << numRollsToTarget(2, 6, 7);
}