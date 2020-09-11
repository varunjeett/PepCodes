// 55 jump game
class Solution {
public:
    //greedy approch, traverse from backward and maintain a last variable, at each instance consider the max jump possible to reach the 'last'
    bool canJump(vector<int>& nums) {
        
        int n=nums.size();
        if(n==1) 
            return true;
        if(nums[0]==0 && n>1)
            return false;
        
        int last=n-1;
        for(int i=n-2; i>=0; i--) {
            if(i+nums[i]>=last)
                last=i;
        }
        if(last==0)
            return true;
        else
            return false;
    }
};

// 1221 :Split a String in Balanced Strings
//maintain a window and keep a count on the L and R in that window , when L and R become equal ,count the window and again start from end of current window(Right+1)
class Solution {
public:
    int balancedStringSplit(string s) {
        int count=0;
        int n=s.length();
        int ll=0;
        int rr=0;
        
        int left=0;
        int right=0;

        
        while(right<n) {
            if(s[right]=='L')
                ll++;
            else
                rr++;
                  
            if(ll==rr){     //count window and update count 
                count++;
                left=right+1;
                right=right+1;
                ll=0;
                rr=0;
                continue;
            }
            
            right++;
        }
        
        return count++;
    }
};

// 1518	
// Water Bottles
class Solution {
public:
    int numWaterBottles(int cur, int ex) {
        int count=0;
        int leftOff=0;   //3
        
        while((cur+leftOff) >= ex ) {
            count+=cur;
            int totalEmpty=cur+leftOff;
            int refilled=totalEmpty/ex;
            
            //for next iteration
            leftOff=totalEmpty%ex;
            cur=refilled;
        }
        return count+cur;
    }
};


// 763. Partition Labels
// A string S of lowercase English letters is given. 
// We want to partition this string into as many parts as possible so that each letter appears in at most one part,
//  and return a list of integers representing the size of these parts.
class Solution {
public:
    vector<int> partitionLabels(string str) {
        int n=str.length();
        if(n==1) return {1}; 
        vector<int> last(26);
        for(int i=0;i<str.length();i++) {
            last[str[i]-'a']=i;
        }

        //key is to keep a window for last occurence, add the window in the answer once we traverse the window completely
        //extend the end if a element comes whose last occurence lies beyond the current end of window;
        
        vector<int> ans;
        int start=0;
        int end=0;
        
        for(int i=0;i<str.length();i++) {
            int lastofCur=last[str[i]-'a'];
            end=max(end,lastofCur);
            if(i==end){
                ans.push_back(end-start+1);
                start=i+1;
                end=i+1;
            }
        }
        
        return ans;
    }
};


//Greedy approach to count all subarrays with max value greater than k.=======================
long findNum(vector<int> &arr,int k) {
    int n=arr.size();

    long total=(n*(n+1))/2;
    long count=0;
    long sum=0;     //contains all subarrays less than max value k
    
    for(int ele:arr) {
        if(ele <= k) 
            count++;
        else
        {
            sum+=(count*(count+1))/2;   //count is the length of longest subarray till now
            //as we encounter a greater element , our chain breaks, hence count set to zero..

            count=0;
        }
    }
    
    sum+=(count*(count+1))/2;   //elements left in chain
    return total-sum;
}