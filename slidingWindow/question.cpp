//sliding window normal.
//refrain from equating characters of the string as there are empty spaces, keep it simple===================================

//leetcode : 3. Longest Substring Without Repeating Characters
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n=s.length();
        int left=0;
        int right=0;
        unordered_set<char> map;
        int len=0;
        
        while(right < n) {
            if(map.find(s[right])==map.end()) {
                map.insert(s[right++]);
                int cur=map.size();
                len=max(len,cur);   
            }
            else{
                map.erase(s[left++]);
            }
        }
        
        return len;
    }
};

//another solution.=======================================

// class Solution {
// public:
//     int lengthOfLongestSubstring(string s) {
//         int left = 0;
//         int right = 0;
//         int maxlen = 0;
//         vector<int> last(255,-1);
        
//         for (; right < s.length(); right++) {
//             if (last[s[right] - ' '] >= left) {
//                 left = last[s[right] - ' '] + 1;
//             }
//             last[s[right] - ' '] = right;
//             maxlen = max(maxlen, right-left+1);
//         }
        
//         return maxlen;
//     }
// };


// 209. Minimum Size Subarray Sum
//can be done by sliding window as well
class Solution {
public:
    bool f(int sum,vector<int>& nums,int len) {
        int rsum=0;
        for(int i=0;i<len;i++)
            rsum+=nums[i];
        
        if(rsum >= sum)
            return true;
        
        for(int i=len;i<nums.size();i++)
        {
            rsum+=nums[i];
            rsum-=nums[i-len];
            
            if(rsum >= sum)
                return true;
        }
        
        return false;
    }
    
    
    int minSubArrayLen(int s, vector<int>& nums) {
        
        int left=0;
        int right=nums.size()+1;
        
        while(left < right)
        {
            int mid=left+(right-left)/2;
            if(f(s,nums,mid))
            {
                right=mid;
            }
            else
                left=mid+1;
            
        }
        
        return (left==nums.size()+1) ? 0 : left;
    }
};