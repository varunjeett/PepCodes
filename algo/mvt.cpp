//based on moore voting algorithm.-===================================

//for elements that appear more than n/k times.==========
// https://www.geeksforgeeks.org/given-an-array-of-of-size-n-finds-all-the-elements-that-appear-more-than-nk-times/

class Solution
{
public:
    int fre(vector<int> &nums, int item)
    {
        int count = 0;
        for (int ele : nums)
        {
            if (ele == item)
                count++;
        }
        return count;
    }

    int candidate(vector<int> &nums)
    {

        int candi = nums[0];
        int count = 0;

        //counting the majority element
        for (int ele : nums)
        {
            if (ele == candi)
                count++;
            else
            {
                count--;
                if (count == 0)
                {
                    count = 1;
                    candi = ele;
                }
            }
        }

        return candi;
    }

    int majorityElement(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return -1;

        int candi = candidate(nums);

        if (fre(nums, candi) > (n / 2))
        { //candidate confirmed
            return candi;
        }

        return -1;
    }
};

//majority element-2::::::::::::::::::::::::::::::::::::::
//not much efficient.....(n-2)
class Solution
{
public:
    int fre(int i, vector<int> &nums)
    {
        int count = 1;
        for (int j = i + 1; j < nums.size(); j++)
        {
            if (nums[i] == nums[j])
            {
                count++;
                swap(nums[j], nums[nums.size() - 1]);
                nums.pop_back();
                j--;
            }
        }
        return count;
    }

    vector<int> majorityElement(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return {};

        vector<int> ans;

        for (int i = 0; i < nums.size(); i++)
        {
            int freq = fre(i, nums);
            if (freq > (n / 3))
            {
                ans.push_back(nums[i]);
            }
            swap(nums[i], nums[nums.size() - 1]);
            nums.pop_back();
            i--;
        }

        return ans;
    }
};

// leetcode 41: first missing positive
class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        int n = nums.size();

        //here we swap similarly to denote that this element is present (remember the negative trick to denote that this element is present)
        for (int i = 0; i < n; i++)
        {
            // int ele=nums[i];
            while (nums[i] != i + 1)
            {
                //this thing is important , do -1 after storing it in long
                long idx = nums[i]; //getting the respective index
                idx = idx - 1;
                if (idx < 0 || idx >= n || nums[idx] == idx + 1)
                { //do not move an  element which is already set
                    break;
                }

                swap(nums[i], nums[idx]);
            }
        }

        int i = 0;
        for (i = 0; i < n; i++)
        {
            if (nums[i] != i + 1)
            {
                return i + 1;
            }
        }

        return i + 1; //consider array of{1,2,3,4}, all elements are at place, after the second loop completes , we have i=4, but the answer is i+1=5;
    }
};

//index detection method.========================
class Solution
{
public:
    int findDuplicate(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 2)
            return nums[0];

        for (int i = 1; i < n; i++)
        {
            while (nums[i] != i)
            {
                int idx = nums[i];
                if (idx < 0 || idx >= n)
                {
                    break;
                }

                //the two elements to be swapped are same: so duplicate found-=======
                if (nums[idx] == nums[i])
                {
                    return nums[idx];
                }

                swap(nums[idx], nums[i]);
            }
        }

        return nums[0];
    }
};