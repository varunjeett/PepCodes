#include <bits/stdc++.h>
using namespace std;

int maxSumIncreasingSS_lr(vector<int> &arr, vector<int> &dp)
{
    int max_ = -1;
    for (int i = 0; i < arr.size(); i++)
    {
        dp[i] = arr[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] < arr[i])
            {
                dp[i] = max(dp[i], dp[j] + arr[i]);
            }
        }
        max_ = max(max_, dp[i]);
    }
    return max_;
}

void maxSumIncreasingSS(vector<int> &arr)
{
    vector<int> dp(arr.size());
    cout << maxSumIncreasingSS_lr(arr, dp) << endl;
    return;
}

int increasing_lr(vector<int> &arr, int N)
{
    vector<pair<int, int>> dp(N); //pair.first=length of longest, pair.second is occurence
    int max_len = 0;
    int count = 0;

    for (int i = 0; i < N; i++)
    {
        dp[i].first = 1;
        dp[i].second = 1;

        for (int j = i - 1; j >= 0; j--)
        {

            if (arr[j] < arr[i])
            {
                if (dp[j].first + 1 > dp[i].first) //considering inside the loop
                {
                    dp[i].first = dp[j].first + 1;
                    dp[i].second = dp[j].second;
                }
                else if (dp[j].first + 1 == dp[i].first)
                {
                    dp[i].second += dp[j].second;
                }
            }
        }

        if (dp[i].first > max_len)
        {
            max_len = dp[i].first;
            count = dp[i].second;
        }
        else if (dp[i].first == max_len) //this will handle the case when there is no supreme/single LIS answer
        {
            count += dp[i].second; //maintaining the count
        }
    }

    return count;
}

int findNumberOfLIS(vector<int> &nums)
{
    int n = nums.size();
    if (n < 2)
        return n;
    return increasing_lr(nums, n);
}

int main()
{

    // int t;
    // cin >> t;
    // while (t-- > 0)
    // {
    //     int len;
    //     cin >> len;
    //     vector<int> arr(len);
    //     int i = 0;
    //     while (i < len)
    //     {
    //         cin >> arr[i];
    //         i++;
    //     }
    //     maxSumIncreasingSS(arr);
    // }
    // return 0;

    vector<int> arr = {2, 2, 2, 2, 2, 2};
    cout << findNumberOfLIS(arr);
}
