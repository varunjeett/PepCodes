// leetcode 84
// first version.==================================

class Solution
{
public:
    vector<int> nsol(vector<int> &arr)
    {
        int n = arr.size();
        vector<int> ans(n, -1);
        stack<int> st;
        st.push(-1);

        for (int i = arr.size() - 1; i >= 0; i--)
        {
            while (st.top() != -1 && arr[i] < arr[st.top()])
            {
                ans[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }

    vector<int> nsor(vector<int> &arr)
    {

        int n = arr.size();
        vector<int> ans(n, n);
        stack<int> st;
    for(int i=arr.size()-1; i>=0; i--)
    {
        st.push(-1);

        for (int i = 0; i < arr.size(); i++)
        {
            while (st.top() != -1 && arr[i] < arr[st.top()])
            {
                ans[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }

    int largestRectangleArea(vector<int> &heights)
    {
        vector<int> nsol_ = nsol(heights);

        for (int ele : nsol_)
        {
            cout << ele << ",";
        }
        cout << endl;

        vector<int> nsor_ = nsor(heights);
        for (int ele : nsor_)
        {
            cout << ele << ",";
        }

        int max_ = 0;

        for (int i = 0; i < heights.size(); i++)
        {

            int area = heights[i] * (nsor_[i] - nsol_[i] - 1);

            max_ = max(max_, area);
        }
        return max_;
    }
};

//second version .=======================================
class Solution
{
public:
    int largestRectangleArea(vector<int> &hei)
    {
        stack<int> st;
        int n = hei.size();
        st.push(-1);
        int max_ = 0;

        for (int i = 0; i < hei.size(); i++)
        {
            while (st.top() != -1 && hei[st.top()] >= hei[i])
            { //left bound neeche hoga, right bound upar se aaega
                int height = hei[st.top()];
                st.pop();
                int maxarea = height * (i - st.top() - 1);
                max_ = max(max_, maxarea);
            }
            st.push(i);
        }

        while (st.top() != -1)
        {
            int height = hei[st.top()];
            st.pop();
            int maxarea = height * (n - st.top() - 1);
            max_ = max(max_, maxarea);
        }
        return max_;
    }
};

//leetcode trapping rainwater
//first version.================================

class Solution
{
public:
    vector<int> GoLeft(vector<int> &arr)
    {   
        //greatest on left , left se right jaenge
        int prev = -1;
        vector<int> ans(arr.size());
        for (int i = 0; i < arr.size(); i++)
        {
            prev = max(arr[i], prev);
            ans[i] = prev;
        }
        return ans;
    }

    vector<int> GoRight(vector<int> &arr)
    { 
        //greatest on right, right se left jaenge
        int prev = -1;
        vector<int> ans(arr.size());
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            prev = max(arr[i], prev);
            ans[i] = prev;
        }
        return ans;
    }

    int trap(vector<int> &height)
    { // 3n time, 2n space
        vector<int> left = GoLeft(height);
        vector<int> right = GoRight(height);

        int ans = 0;
        for (int i = 0; i < height.size(); i++)
        {
            ans += min(left[i], right[i]) - height[i];
        }

        return ans;
    }
};

//second version============================= //n time , n space
class Solution
{
public:
    int trap(vector<int> &height)
    {
        stack<int> st;
        st.push(-1);
        int ans = 0;
        for (int i = 0; i < height.size(); i++)
        {
            while (st.top() != -1 && height[st.top()] <= height[i])
            {
                int idx = st.top();
                st.pop();
                if (st.top() != -1)
                {
                    int width = i - st.top() - 1;
                    int length = min(height[i], height[st.top()]) - height[idx];
                    ans += (width * length);
                }
            }
            st.push(i);
        }

        return ans;
    }
};

//third version .==============================// n time , 1 space
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int n = height.size();
        if (n == 0 || n == 1 || n == 2)
            return 0;

        int leftmax = -1;
        int rightmax = -1;
        int li = 0;
        int ri = n - 1;
        int water = 0;

        while (li < ri)
        {
            leftmax = max(leftmax, height[li]);
            rightmax = max(rightmax, height[ri]);

            if (leftmax >= rightmax)
            {
                water += rightmax - height[ri--];
            }
            else
            {
                water += leftmax - height[li++];
            }
        }
        return water;
    }
};

// leetcode 895 maximum frequency stack
class FreqStack
{

    int maxfreq = 0;
    unordered_map<int, int> val_freq;
    unordered_map<int, stack<int>> freq_values;

public
    FreqStack()
    {
        maxfreq = 0;
    }

public
    void push(int x)
    {
        val_freq[val]++;
        freq_values[val_freq[val]].push(val);
        if (maxfreq < val_freq[val])
            maxfreq = val_freq[val];
    }

public
    int pop()
    {

        if (freq_values[maxfreq].size() == 0)
            return -1;
        int ele = freq_values[maxfreq].top();
        freq_values[maxfreq].pop() if (freq_values[maxfreq].size() == 0) maxfreq--;
        val_freq[ele]--;
        return ele;
    }
}

//decode string 394
class Solution
{
public:
    string decodeString(string s)
    {
        vector<char> st;
        for (char ch : s)
        {
            if (ch == ']')
            {
                string temp = "";

                while (st.size() != 0 && st.back() != '[')
                {
                    temp += st.back();
                    st.pop_back();
                }

                st.pop_back();
                reverse(temp.begin(), temp.end()); //this substring has to be repeated.

                string times = ""; //getting no of times the above string has to be repeated.
                while (st.size() != 0 && isdigit(st.back()))
                {
                    times += st.back();
                    st.pop_back();
                }
                reverse(times.begin(), times.end());

                int time = stoi(times);

                while (time-- > 0)
                    for (char c : temp)
                        st.push_back(c);
            }
            else
                st.push_back(ch);
        }

        string ans = "";
        for (char c : st)
            ans += c;

        return ans;
    }
};

//maximum sliding window.==========================================
class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> ng(n, n);
        stack<int> st;

        //getting the next greater element
        for (int i = 0; i < n; i++)
        {
            while (st.size() != 0 && nums[st.top()] < nums[i])
            {
                int idx = st.top();
                st.pop();
                ng[idx] = i;
            }
            st.push(i);
        }

        vector<int> ans;
        for (int i = 0; i <= n - k; i++)
        {
            int j = i;

            //consider case of window : (1,2,3,4) jumping to the j whose next greater lies outside of window,tht is max for that window.
            while (ng[j] < i + k) //(i+k-1)- i +1)=k:::len=last-first+1
            {
                j = ng[j];
            }

            ans.push_back(nums[j]); //jis j ke liye, next greater window se bahar hai, vhi us window ka max hai
        }

        return ans;
    }
};

//maximum sliding window 2
class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {

        vector<int> res;
        int max_till = INT_MIN;
        for (int i = 0; i < k; i++)
            max_till = max(max_till, nums[i]);
        res.push_back(max_till);
        int start = 0;
        for (int i = k; i < nums.size(); i++)
        {
            if (nums[start] == max_till)
            {
                max_till = nums[start + 1];
                for (int j = start + 1; j <= i; j++)
                    max_till = max(max_till, nums[j]);
            }
            else
                max_till = max(max_till, nums[i]);
            start++;
            res.push_back(max_till);
        }
        return res;
    }
};

// 32. Longest Valid Parentheses
// Simple, mark the invalid char by asterik using stack, then count longest stretch without asterik 
class Solution {
public:
    int longestValidParentheses(string s) 
    {
        if(s.length()==0)
            return 0;
            
        stack<int> st;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='(')
                st.push(i);
            else
            {
                if(st.size()!=0  && s[st.top()]=='(')
                    st.pop();
                else
                    st.push(i);
            }
        }
        
        if(st.size()==0)
            return s.length();
                                           
        
        while(st.size()!=0)
        {
            int rvtx=st.top();
            st.pop();
            
            s[rvtx]='*';
        }
        
        // cout<<s<<endl;
        
        int mx=0;
        int count=0;
        
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='*')
            {
                mx=max(mx,count);
                count=0;
            }
            else
                count++;
            
            mx=max(mx,count);
        }
        
        return mx;
    }
};


//Important question;;;;;;;;;;;;;;;;;;;;;;;

//case 1: "123456" something like this , now removing chracters fromthe back will give us the minimum
//case 2:  "198345" initially remove 9 and place 8 there, then remove 8 and place 3 there, now it becomes "1345",  now of k is left , remove from back
// handle leading zeroes

class Solution {
public:
    string removeKdigits(string num, int k) {
        vector<char>st;
        st.push_back('@');
        for(char ch: num){
            while(st.back()!='@' && k>0 && st.back() > ch){
                st.pop_back();
                k--;
           }
           st.push_back(ch);
        }
        
        int i=st.size()-1;
        while(k-- > 0) 
            st[i--]='@';                     //removing left over
        
        for(int i=0; i<st.size();i++){       //removing leading zeroes
            if(st[i]!='@' && st[i]!='0') break;
            st[i]='@';
        }
        
        string ans="";
        for(int i=0; i<st.size();i++){   //creating answer back
            if(st[i]!='@') 
              ans+=st[i];
        }
        
        if(ans=="") 
            return "0";                 //important case
        return ans;                     //back to string
    }
};