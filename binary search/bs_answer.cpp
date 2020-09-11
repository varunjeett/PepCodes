#include <iostream>
#include <vector>
using namespace std;

//https://www.geeksforgeeks.org/allocate-minimum-number-pages/
//Given number of pages in n different books and m students. The books are arranged in ascending order of number of pages.
//Every student is assigned to read some consecutive books.
//The task is to assign books in such a way that the maximum number of pages assigned to a student is minimum.

//it finds whether we can divide the array into less than k subset with max sum 'max'_
bool isvalid(vector<int> &arr, long max_, int k)
{
    long sum = 0;
    int count = 1;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > max_)
            return false;

        if (sum + arr[i] > max_)
        {
            count++;
            sum = arr[i];
            if (count > k)
                return false;
            continue;
        }
        sum += arr[i];
    }

    return true;
}

long find(vector<int> &arr, int k)
{

    if (arr.size() < k)
        return -1;
    long left = 0;
    long right = 0;
    for (int ele : arr)
        right += ele;

    long ret = +1e8;
    while (left <= right)
    {
        long mid = left + (right - left) / 2;
        if (isvalid(arr, mid, k))
        {
            ret = min(ret, mid);
            right = mid - 1;
        }
        else
            left = mid + 1;
    }

    return ret;
}

int main()
{
    //code
    int t;
    cin >> t;
    while (t-- > 0)
    {
        int i = 0;
        int len;
        cin >> len;
        vector<int> arr(len);
        while (i != len)
        {
            cin >> arr[i++];
        }
        int k;
        cin >> k;
        cout << find(arr, k) << endl;
    }
    return 0;
}

//painters problem
// https://practice.geeksforgeeks.org/problems/the-painters-partition-problem/0/
#include <iostream>
#include <vector>
using namespace std;

bool isvalid(vector<int> &arr, long max_, int k)
{
    long sum = 0;
    int count = 1;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > max_)
            return false;

        if (sum + arr[i] > max_)
        {
            count++;
            sum = arr[i];
            if (count > k)
                return false;
            continue;
        }
        sum += arr[i];
    }

    return true;
}

long find(vector<int> &arr, int k)
{

    long left = 0;
    long right = 0;
    for (int ele : arr)
        right += ele;

    long ret = +1e8;
    while (left <= right)
    {
        long mid = left + (right - left) / 2;
        if (isvalid(arr, mid, k))
        {
            ret = min(ret, mid);
            right = mid - 1;
        }
        else
            left = mid + 1;
    }

    return ret;
}

int main()
{
    //code
    int t;
    cin >> t;
    while (t-- > 0)
    {
        int k;
        cin >> k; //painters
        int i = 0;
        int len;
        cin >> len;
        vector<int> arr(len);
        while (i != len)
        {
            cin >> arr[i++];
        }
        cout << find(arr, k) << endl;
    }
    return 0;
}


//875. Koko Eating Bananas
class Solution
{
public:
    bool isValid(vector<int> &arr, int max_, int speed)
    {
        if (speed <= 0)
            return false;

        int hours = 0;
        for (int ele : arr)
        {
            hours += ele / speed;
            hours += (ele % speed == 0) ? 0 : 1;
            if (hours > max_)
                return false;
        }
        return true;
    }

    int minEatingSpeed(vector<int> &arr, int hr)
    {
        int n = arr.size();
        if (n == 0)
            return 0;
        int left = 0;
        int right = 0;
        for (int ele : arr)
            right = max(right, ele); //max speed possible

        int ans = INT_MAX;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (isValid(arr, hr, mid))
            {
                ans = min(ans, mid); //store the min till now
                right = mid - 1;     //speed decrease
            }
            else
                left = mid + 1; //speed increase
        }
        return ans;
    }
};