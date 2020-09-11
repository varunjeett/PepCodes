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

//here increasing and decreasing means strictly============================
int increasing_lr(vector<int> &arr, vector<int> &dp)
{
    int N = arr.size();
    int max_ = -1; //maintains the max length of each sequence
    for (int i = 0; i < N; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] < arr[i])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_ = max(max_, dp[i]);
    }
    return max_;
}

int decreasing_lr(vector<int> &arr, vector<int> &dp)
{
    int N = arr.size();
    int max_ = -1;

    for (int i = 0; i <= N - 1; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] > arr[i])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_ = max(max_, dp[i]);
    }

    return max_;
}

int increasing_rl(vector<int> &arr, vector<int> &dp)
{
    int N = arr.size();
    int max_ = -1;

    for (int i = N - 1; i >= 0; i--)
    {
        for (int j = i + 1; j <= N - 1; j++)
        {
            if (arr[i] > arr[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_ = max(max_, dp[i]);
    }

    return max_;
}

int decreasing_rl(vector<int> &arr, vector<int> &dp)
{
    int N = arr.size();
    int max_ = -1;

    for (int i = N - 1; i >= 0; i--)
    {
        for (int j = i + 1; j <= N - 1; j++)
        {
            if (arr[i] < arr[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_ = max(max_, dp[i]);
    }

    return max_;
}

void rightToLeft()
{
    vector<int> arr = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    vector<int> dp(arr.size(), 1);
    cout << increasing_rl(arr, dp) << endl;
    // display(dp);
    //cout << decreasing_rl(arr, dp) << endl;
    // display(dp);
}

void leftToRight()
{
    vector<int> arr = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    vector<int> dp(arr.size(), 1);
    // cout<<increasing_lr(arr, dp)<<endl;
    // display(dp);
    cout << decreasing_lr(arr, dp) << endl;
    // display(dp);
}

void bitonic()
{
    vector<int> arr = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    vector<int> dp1(arr.size(), 1);
    vector<int> dp2(arr.size(), 1);

    increasing_lr(arr, dp1);
    increasing_rl(arr, dp2);

    for (int ele : dp1)
        cout << ele << " ";

    cout << endl;

    for (int ele : dp2)
        cout << ele << " ";

    int max_ = -1;
    int pos=0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (dp1[i] + dp2[i] - 1 > max_)
        {
            max_ = dp1[i] + dp2[i] - 1;
            pos=i;
        }
        
    }
    cout << max_ <<"@"<<pos<<endl;
}

void inverseBitonic()
{
    vector<int> arr = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    vector<int> dp1(arr.size(), 1);
    vector<int> dp2(arr.size(), 1);
    decreasing_lr(arr, dp1);
    decreasing_rl(arr, dp2);
    int max_ = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        max_ = max(max_, (dp1[i] + dp2[i] - 1));
    }
    cout << max_;
}

void removeToSort()
{
    vector<int> arr = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    int n = arr.size();
    vector<int> dp(n, 1);
    int max_ = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] <= arr[i])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_ = max(max_, dp[i]);
    }
    cout << max_ << endl;
    cout << n - max_;
}

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

void maxSumIncreasingSS()
{
    vector<int> arr = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 154};
    vector<int> dp(arr.size());
    cout << maxSumIncreasingSS_lr(arr, dp) << endl;
}

//lc 334 ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
bool increasingTriplet(vector<int> &nums)
{
    int n = nums.size();
    if (n <= 2)
        return false;

    int a = +1e8, b = +1e8; // at any time ,we maintain, the two smallest element such that a < b

    for (int ele : nums)
    {
        if (ele > b)
            return true;
        else if (ele > a)
            b = min(b, ele);
        else if (ele < a)
            a = ele;
    }
    return false;
}

void lc334()
{
    vector<int> arr = {5, 10, 7, 1, 10};
    cout << (boolalpha) << increasingTriplet(arr);
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

        else if (dp[i].first == max_len)  //this will handle the case when there is no supreme/single LIS answer
        {
            count += dp[i].second;       //maintaining the count
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

void solve()
{
    // leftToRight();
    // rightToLeft();
    bitonic();
    // inverseBitonic();
    // removeToSort();
    //  maxSumIncreasingSS();
    // lc334();
    vector<int> arr = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9};
    cout << findNumberOfLIS(arr);
}

int main()
{
    solve();
}
