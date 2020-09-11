// 368. Largest Divisible Subset
//LIS type
class Solution
{
public:
    vector<int> largestDivisibleSubset(vector<int> &nums)
    {
        if (nums.size() == 0)
            return {};
        if (nums.size() == 1)
            return nums;

        sort(nums.begin(), nums.end());

        int n = nums.size();
        vector<int> count(n, 1); //no of elements
        vector<int> prev(n, -1); //idex of prev divisor

        int max_idx = -1; //index of last element of the biggst set
        int mx = -1;      //size of biggest set

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] % nums[j] == 0 && count[j] + 1 > count[i])
                {
                    count[i] = count[j] + 1;
                    prev[i] = j; //setting the prev divisor
                }
            }

            if (count[i] > mx)
            {
                max_idx = i;
                mx = count[i];
            }
        }

        vector<int> ans(mx);
        int i = mx - 1;
        while (max_idx >= 0)
        {
            ans[i--] = nums[max_idx];
            max_idx = prev[max_idx]; //changing the index to prev's divisor
        }
        return ans;
    }
};

// 238. Product of Array Except Self without division operator
//O N TIME
//0 1 SPACE
class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return {};

        vector<int> arr(n, 1);

        //IN ONE GO, FROM LEFT TO RIGHT

        int val1 = 1; //product of subarray from 0 to i-1
        for (int i = 0; i < n; i++)
        {
            arr[i] *= val1;
            val1 *= nums[i];
        }

        //IN ONE GO, FROM RIGHT TO LEFT

        int val2 = 1; //product of subarray from i+1 to n-1
        for (int i = n - 1; i >= 0; i--)
        {
            arr[i] *= val2;
            val2 *= nums[i];
        }

        return arr;
    }
};

// 646. Maximum Length of Pair Chain
class Solution
{
public:
    int findLongestChain(vector<vector<int>> &pairs)
    {
        int n = pairs.size();
        if (n == 0)
            return 0;

        sort(pairs.begin(), pairs.end(), [](const vector<int> &t, const vector<int> &o) {
            return t[1] < o[1];
        });

        //  sort(pairs.begin(),pairs.end(),[](const vector<int> &t,const vector<int> &o) -> bool{
        //     return t[1] < o[1];
        // });

        //single element is chain of 1
        vector<int> lis(n, 1);
        int mx = 0;

        for (int i = 0; i < n; i++)
        {
            lis[i] = 1;

            //finding the maximum chain for each pair
            for (int j = 0; j < i; j++)
            {
                if (pairs[j][1] < pairs[i][0])
                {
                    if (lis[j] + 1 > lis[i])
                    {
                        lis[i] = lis[j] + 1;
                    }
                }
            }

            mx = max(mx, lis[i]);
        }
        return mx;
    }
};
