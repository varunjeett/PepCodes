// 53. Maximum Subarray Sum
// KADANE'S ALGO
class Solution
{
public:
    int maxSubArray(vector<int> &arr)
    {
        int n = arr.size();
        if (n <= 1)
            return n == 0 ? 0 : arr[0];
        int max_end_here = 0;
        int max_ = INT_MIN;
        for (int i = 0; i < n; i++)
        {
            max_end_here = max(arr[i], max_end_here + arr[i]); //the key is to maintain the maximum ending subarray at that point
            //for any i, the max could be max_ending at (i-1 + arr[i])  or excluding the previous [i-1] and including only current value

            max_ = max(max_, max_end_here);
        }

        return max_;
    }
};

//152. Maximum Product Subarray
class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;

        int prev_min = nums[0];
        int prev_max = nums[0];
        int ans = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {

            // each element could be either positive negative or zero
            // for positive ele,we'll get the max from prev_max*ele or only ele(if prev_max is negative)
            // for negative ele,we can get the max from prev_min or only ele

            // if current element is negative ; prev_min gives us the max value till now.
            // if current element is positive ; prev_max gives us the max value till now.

            int cur_max = max(nums[i], max(prev_max * nums[i], prev_min * nums[i]));
            int cur_min = min(nums[i], min(prev_max * nums[i], prev_min * nums[i]));

            ans = max(ans, cur_max);
            prev_min = cur_min;
            prev_max = cur_max;
        }
        return ans;
    }
};

// 560. Number of Subarray whose sum Equals K :::::::::::
class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        unordered_map<int, int> map;
        int cursum = 0;
        int count = 0;

        // k=3
        // 1 1 1 2
        // now , we have cursum=5, so we need a subarray of sum=2, so that we can virtually subtract them and
        // get the final sum as 5-2==k(3), hence subarray found, increment count

        for (int i = 0; i < n; i++)
        {
            cursum += nums[i];

            if (cursum == k)
                count++;

            int target = cursum - k;
            //single element case in handled here
            if (map.find(cursum - k) != map.end()) //till now map contains subarray's sum before
                count += map[cursum - k];

            map[cursum]++; //adding cursum  //atlast add the cursum
        }

        return count;
    }
};

// 523. Continuous Subarray Sum
// Given a list of non-negative numbers and a target integer k,
// write a function to check if the array has a continuous subarray of size
//  at least 2 that sums up to a multiple of k,
// that is, sums up to n*k where n is also an integer.

class Solution
{
public:
    bool checkSubarraySum(vector<int> &nums, int k)
    {
        //remainder logic to find the divisibility
        if (nums.size() == 0)
            return false;

        int csum = 0;
        unordered_map<int, int> map;
        map[0] = -1;
        for (int i = 0; i < nums.size(); i++)
        {
            csum += nums[i];
            int rem;
            if (k == 0) //when k==0, the only multiple possible is zero, so we need to subtract csum from csum ,to get 0,that means remainder should be csum
                rem = csum;
            else
                rem = (csum % k);

            // dont overwrite same remainder with new index ,(being greedy here,to get fartest index)
            if (map.find(rem) != map.end())
            {
                //map[rem] is the index
                if (i - map[rem] >= 2)
                    return true;
            }
            else
                map[rem] = i;
        }

        return false;
    }
};

//no of subarray with given xor
int Solution::solve(vector<int> &a, int k)
{
    int n = a.size();

    int c = 0;
    int runningXor = 0;
    unordered_map<int, int> map;
    for (int i = 0; i < n; i++)
    {
        runningXor = (runningXor ^ a[i]);

        if (runningXor == k)
            c++;

        // tricky part  Similiar to this for subarray sum(target = cursum - k);
        int target = (k ^ runningXor); // (a^b)=c ,(c^b=a),(a^c=b)

        //single element case in handled here
        if (map.find(target) != map.end())
        {
            c += map[t];
        }

        map[runningXor]++;
    }

    return c;
}

// 974. Subarray Sums Divisible by K
// https://www.youtube.com/watch?v=u9m-hnlcydk

// i se start hoke j pe khatam hone wala
// Let there be a subarray (i, j) whose sum is divisible by k
//   sum(i, j) = sum(0, j) - sum(0, i-1)
// Sum for any subarray can be written as q*k + rem where q
// is a quotient and rem is remainder
// Thus,
//     sum(i, j) = (q1 * k + rem1) - (q2 * k + rem2)
//     sum(i, j) = (q1 - q2)k + (rem1-rem2)

// For our condition , we need (rem1 = rem2) because in any other case, (rem1-rem2) will lie in between (1 to k-1), which is not divisible by k
// We see, for sum(i, j) i.e. for sum of any subarray to be
// divisible by k, the RHS should also be divisible by k.
// (q1 - q2)k is obviously divisible by k, for (rem1-rem2) to
// follow the same,  where
//     rem1 = Sum of subarray (0, j) % k
//     rem2 = Sum of subarray (0, i-1) % k

class Solution
{
public:
    int subarraysDivByK(vector<int> &nums, int k)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        int cursum = 0;
        vector<int> rem(k);

        //based on the property of same remainder
        for (int i = 0; i < n; i++)
        {
            cursum += nums[i];
            int idx = (cursum % k + k) % k; //handles both positive and negative numbers
            rem[idx]++;
        }

        int count = 0;
        count += rem[0]; //for zero, its a special case, as the subarray(starting with 0-index ) with remainder 0 is itself is divisible by k.

        for (int ele : rem)
        {
            // For our condition , we need (rem1 = rem2) because in any other case,
            // (rem1-rem2) will lie in between (1 to k-1), which is not divisible by k
            // For subarrays of same remainder, we choose 2 at a time to virtually subtract those subarrays and form the required subarray with sum divisible by K
            count += (ele * (ele - 1)) / 2; //N choose 2= n*(n-1)/2;
        }
        return count;
    }
};

// Given an array A[] of N positive integers.
// The task is to find the maximum of j - i subjected to the constraint of A[i] <= A[j].
// https://practice.geeksforgeeks.org/problems/maximum-index/0
// the key point is to get the farthest element for every element of the given array which is greater or equal to the current element

typedef long long int lli;
int find(vector<lli> &arr)
{
    int n = arr.size();
    vector<lli> ll(n);
    vector<lli> rr(n);

    int mn = arr[0];
    ll[0] = mn;
    for (int i = 1; i < n; i++)
    {
        // mn=min(mn,arr[i]);
        if (mn > arr[i])
        {
            mn = arr[i];
        }
        ll[i] = mn;
    }

    int mx = arr[n - 1];
    rr[n - 1] = mx;
    for (int i = n - 2; i >= 0; i--)
    {
        if (mx < arr[i])
        {
            mx = arr[i];
        }
        rr[i] = mx;
    }

    int i = 0;
    int j = 0;
    int ans = -1;
    while (i < n && j < n)
    {
        if (ll[i] <= rr[j])
        {
            ans = max(ans, j - i);
            j++;
        }
        else
            i++;
    }
    return ans;
}

//the key here is to do it in O(n) time and O(1) space,IMPORTANT FROM INTERVIEW
//we maintain the og that index points at the last unique index
//while traversing if we see a element which is different from the element at OG , we place it at OG+1, and update OG to OG+1
//we just overwrite the duplicates with unique ones

//vector.erase() and vector.clear() work in O(N) time
class Solution
{
public:
    inline void swap(int idx1, int idx2, vector<int> &nums)
    {
        int t = nums[idx2];
        nums[idx2] = nums[idx1];
        nums[idx1] = t;
    }

    int removeDuplicates(vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;

        int og, j;
        og = 0;
        j = 1;

        for (j = 1; j < nums.size(); j++)
        {
            if (nums[j] != nums[og])
            {
                if (og + 1 != j)
                {
                    swap(og + 1, j, nums);
                }
                og++;
            }
        }

        return og + 1;
    }
};

// Given a sorted array nums, remove the duplicates in-place
// such that duplicates appeared at most twice and return the new length.
class Solution
{
public:
    inline void swap(int idx1, int idx2, vector<int> &nums)
    {
        int t = nums[idx2];
        nums[idx2] = nums[idx1];
        nums[idx1] = t;
    }
    int removeDuplicates(vector<int> &nums)
    {
        if (nums.size() <= 2) //if array of length 2 is there, no element could appear more than two times
            return nums.size();

        int og, j;
        og = 1;

        for (j = 2; j < nums.size(); j++)
        {
            if (nums[j] != nums[og])
            {
                swap(og + 1, j, nums);
                og++;
            }
            else if (nums[j] != nums[og - 1])
            {
                swap(og + 1, j, nums);
                og++;
            }
        }

        return og + 1;
    }
};

//maximum consective ones
class Solution
{
public:
    int findMaxConsecutiveOnes(vector<int> &a)
    {
        if (a.size() == 0)
            return 0;
        int len = 0;
        int i, j;

        j = 0;
        //go till first one is found
        while (j != a.size() && a[j] != 1)
            j++;

        i = j;
        int sum = 1;
        while (j != a.size())
        {
            //go till subarray consists of only ones
            while (j != a.size() && (j - i + 1) == sum)
            {
                len = max(len, j - i + 1);
                j++;

                //at last point, dont go out of bound
                if (j != a.size())
                    sum += a[j];
            }

            //when j comes at zero, again find the next one
            while (j != a.size() && a[j] != 1)
                j++;

            i = j;
            sum = 1;
        }

        return len;
    }
};

// Given an array A of 0s and 1s, we may change up to K values from 0 to 1.
// Return the length of the longest (contiguous) subarray that contains only 1s.
class Solution
{
public:
    int longestOnes(vector<int> &a, int k)
    {
        int i = 0;
        int j = 0;

        int ct = 0;
        int ln = 0;

        //initial window of size 1
        if (a[0] == 0)
            ct++;

        while (i < a.size() && j < a.size())
        {
            //when window distorts correct it
            if (i > j)
            {
                j = i;
                if (i < a.size())
                {
                    ct = 0;
                    if (a[i] == 0)
                        ct++;
                }
            }

            //maintain of window with no of zeroes maximum to k
            while (j < a.size() && ct <= k)
            {
                ln = max(ln, j - i + 1);
                j++;
                if (j < a.size() && a[j] == 0)
                    ct++;
            }

            if (a[i] == 0)
                ct--;
            i++;
        }
        return ln;
    }
};

//by two pointer approach
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        if (nums.size() <= 2)
            return {};

        vector<vector<int>> arr;

        sort(nums.begin(), nums.end());

        int i = 0;
        while (i < nums.size() - 2)
        {
            int tgt = (0 - nums[i]);
            int j = i + 1;
            int k = nums.size() - 1;

            while (j < k)
            {

                if (nums[j] + nums[k] > tgt)
                {
                    //first incremnets, then check if the previous and current is same or not, if yes then keep incrementing
                    k--;
                    while (k >= 0 && nums[k] == nums[k + 1])
                        k--;
                }
                else if (nums[j] + nums[k] < tgt)
                {
                    //first incremnets, then check if the previous and current is same or not, if yes then keep incrementing
                    j++;
                    while (j < nums.size() && nums[j] == nums[j - 1])
                        j++;
                }
                else
                {
                    cout << i << " " << j << " " << k << endl;
                    arr.push_back({nums[i], nums[j], nums[k]});

                    //first incremnets, then check if the previous and current is same or not, if yes then keep incrementing
                    k--;
                    while (k >= 0 && nums[k] == nums[k + 1])
                        k--;

                    //first incremnets, then check if the previous and current is same or not, if yes then keep incrementing
                    j++;
                    while (j < nums.size() && nums[j] == nums[j - 1])
                        j++;
                }
            }

            //first incremnets, then check if the previous and current is same or not, if yes then keep incrementing

            i++;
            while (i < nums.size() && nums[i] == nums[i - 1])
                i++;
        }

        return arr;
    }
};

// 493. Reverse Pairs
// Based on modified merge sort
// nlogn complexity
class Solution
{
public:
    //merge function is of 3*O(n)
    int merge(int st, int mid, int ed, vector<int> &nums)
    {
        int ct = 0;
        //counting inversions

        //here, as we need to check (nums[i] > 2*nums[j]), so we have to first count them and then sort them
        //then put the sorted array back into nums
        int i, j, k;
        k = 0;

        i = st;
        j = mid + 1;
        while (i <= mid && j <= ed)
        {
            long long int a = nums[i];
            long long int b = nums[j];
            b = b * 2;

            if (a > b)
            {
                //total inversions on that particular jth element.
                ct += (mid - i + 1);
                j++;
            }
            else
                i++;
        }

        //mergeing the two sorted arrays
        vector<int> temp(ed - st + 1);
        k = 0;
        i = st;
        j = mid + 1;
        while (i <= mid && j <= ed)
        {
            if (nums[i] >= nums[j])
            {
                temp[k++] = nums[j++];
            }
            else
            {
                temp[k++] = nums[i++];
            }
        }

        while (i <= mid)
        {
            temp[k++] = nums[i++];
        }

        while (j <= ed)
        {
            temp[k++] = nums[j++];
        }

        //writng back the temp array into nums
        i = 0;
        for (k = st; k <= ed; k++)
        {
            nums[k] = temp[i++];
        }

        return ct;
    }

    //log n time
    int rev(int st, int ed, vector<int> &nums)
    {
        if (st >= ed)
            return 0;

        int mid = st + (ed - st) / 2;
        int ll = rev(st, mid, nums);
        int rr = rev(mid + 1, ed, nums);

        int self = merge(st, mid, ed, nums);

        return (ll + rr + self);
    }

    int reversePairs(vector<int> &nums)
    {
        int n = nums.size();
        if (n <= 1)
            return 0;

        return rev(0, nums.size() - 1, nums);
    }
};

// Equilibrium point , sum of left elements is equal to sum of right elements
// Naive-> go for every index , and loop for left maintain sum, loop in right maintain sum, O(n*n)
// Better-> maintain prefix sum array, for every index,we can get left elements sum and right elements sum (n time , n space)
//             left elements sum : prefix[idx-1] , left elements sum : prefix[last]-prefix[idx]
// Best->  Keep whole array sum in a variable, at every index , keep substracting the elements on the left , and add them in other variable, say lsum
// At any point, when value of lsum==total sum, thats the index

int pivotIndex(vector<int> &nums)
{
    int n = nums.size();

    if (n == 0)
        return -1;

    if (n == 1)
        return 0;

    int right = 0;
    for (int ele : nums)
    {
        right += ele;
    }

    int left = 0;
    for (int i = 0; i < n; i++)
    {
        right -= nums[i];

        if (left == right)
            return i;

        left += nums[i];
    }
    return -1;
}

class Solution
{
public:
    // naive : traverse at every index, and loop in left and right section and check conditions (n*n time)

    // better : maintain two bool arrays for the increasig and decreasing condtions , an index that satisfy both true, will be our answer (3n time and 2n space), further we can jst keep right bool array and maintain left condition while traversing, (2n time and n space)

    // best : starting from left, go till the maximum point, starting from right, go till maximum point , if both equal and in the middle of the array , then answer is true
    bool validMountainArray(vector<int> &arr)
    {

        // There could be jst one mountain point in an array(stricly increasing decreasing condition)

        //idx should not the first or last index
        int n = arr.size();

        if (n <= 2)
            return false;
        int left = 0;
        int right = n - 1;

        while ((left != n - 1) && arr[left] < arr[left + 1])
            left++;

        while ((right != 0) && arr[right - 1] > arr[right])
            right--;

        if (left == right && right > 0 && right < n - 1)
            return true;

        return false;
    }
};