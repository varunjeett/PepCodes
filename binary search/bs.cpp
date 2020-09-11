#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

//greatest of the smaller
int floor_(vector<int> &arr, int tar)
{
    int ans = -1e8;
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= tar)
        {
            if (arr[mid] == tar)
                return tar;
            ans = max(ans, arr[mid]);
        }

        if (tar < arr[mid])
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
            //we are moving towards the greater, but every element is greater and we need smaller values for floor hence break
            if (left >= 0 && left < arr.size() && arr[left] > tar)
                break;
        }
    }
    return ans;
}

//smallest of the greater
int ceil_(vector<int> &arr, int tar)
{
    int ans = +1e8;
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= tar)
        {
            if (arr[mid] == tar)
                return tar;
            ans = min(ans, arr[mid]);
        }

        if (tar < arr[mid])
        {
            right = mid - 1;
            //we are moving towards the smaller, but every element is smaller and we need greater values for ceil hence break
            if (right >= 0 && right < arr.size() && arr[right] < tar)
                break;
        }
        else
        {
            left = mid + 1;
        }
    }
    return ans;
}

int bs_reverse(vector<int> &arr, int target)
{
    int n = arr.size();
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] > target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

int countPair(vector<int> &nums, int mid)
{
    int left = 0;
    int right = 0;
    int count = 0;
    while (right < nums.size())
    {
        while (nums[right] - nums[left] > mid)
        {
            left++;
        }
        count += right - left;
        right++;
    }
    return count;
}

int smallestDistancePair(vector<int> &nums, int k)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int left = 0;
    int right = nums[n - 1] - nums[0];

    while (left < right)
    {
        int mid = left + (right - left) / 2;
        int num = countPair(nums, mid);
        cout << left << "," << right << "-> " << mid << " has " << num << " pairs" << endl;

        if (num >= k)
        {
            right = mid; //consideer the case of [0,2,3,4,4,4,....8] array of differences
        }
        else
            left = mid + 1;
    }

    return left;
}

void ques()
{
    vector<int> arr = {1, 4, 5, 6, 7, 8, 9, 9, 10, 10, 10};
    vector<int> arr2 = {1, 2, 5, 6};
    cout << smallestDistancePair(arr2, 6);
}
void solve()
{

    // vector<int> arr = {67, 34, 12, 10, 9, 7, 4, 2, 1};
    // // cout << floor_(arr,7) <<endl;
    // cout << bs_reverse(arr, 67);

    // vector<int> arr = {3, 6, 7, 11};
    // cout << minEatingSpeed(arr, 8);

    ques();
}

int main()
{
    solve();
    return 0;
}
