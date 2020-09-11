//leetcode : 34. Find First and Last Position of Element in Sorted Array
class Solution
{
public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        static int fast_io = []() { std::ios::sync_with_stdio(false); cin.tie(nullptr); return 0; }();

        int n = nums.size();
        if (n == 0 || (n == 1 && target != nums[0]))
            return {-1, -1};

        int start = 0;
        int end = nums.size() - 1;

        while (start <= end)
        {
            int mid = start + (end - start) / 2;
            if (nums[mid] == target)
            {
                int left = mid;
                int right = mid;
                while (left - 1 >= 0 && nums[left - 1] == target)
                    left--;
                while (right + 1 < n && nums[right + 1] == target)
                    right++;

                return {left, right};
            }

            else if (nums[mid] > target)
                end = mid - 1;
            else
                start = mid + 1;
        }

        return {-1, -1};
    }
};

//leetcode : 278. First Bad Version

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution
{
public:
    int firstBadVersion(int n)
    {
        if (n == 0)
            return -1;

        int left = 0;
        int right = n - 1;
        int min_ = INT_MAX;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (isBadVersion(mid + 1))
            {
                min_ = min(min_, mid + 1); //mid+1 is the value against the mid index
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        return min_;
    }
};

//leetcode : 33. Search in Rotated Sorted Array
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n=nums.size();
        if(n==0) return -1;
        
        int left=0;     int right=n-1;
        while(left<=right) {
            
            int mid=left+(right-left)/2;
            if(nums[mid]==target)
                return mid;
            
            if(nums[left]<=nums[mid])   //left sorted
            {
                if(nums[left]<=target && target<nums[mid])
                    right=mid-1;
                else
                    left=mid+1;
            }
            else                        //right is sorted
            {
                if(nums[mid]<target && target<=nums[right])
                    left=mid+1;
                else
                    right=mid-1;   
            }       
        }
        return -1;
    }
};

// Since the mid element can only move (mid-1 to mid+1) so we ll check the three,
// All the elements from (0 to mid-2) will be less/equal to the smallest of the three (mid-1,mid,mid+1)
// All the elements from (mid+2 to last) will be greater/equal to the boggest of the three (mid-1,mid,mid+1)

//search in a nearly sorted array:
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n=nums.size();
        if(n==0) return -1;
        
        int left=0;     int right=n-1;
        while(left<=right) {
            
            int mid=left+(right-left)/2;
            
            if(nums[mid]==target)
                return mid;
            
            if(nums[left]<=nums[mid])   //left sorted
            {
                if(nums[left]<=target && target<nums[mid])
                    right=mid-1;
                else
                    left=mid+1;
            }
            else                        //right is sorted
            {
                if(nums[mid]<target && target<=nums[right])
                    left=mid+1;
                else
                    right=mid-1;   
            }       
        }
        return -1;
    }
};

//search an element in a bitonic array ;===============================
//dividing the array and aply bs on ascending and descending part.==========================
int bs(vector<int> &arr, int target, int l, int r)
{
    int left=l;
    int right=r;

    while(left<=right)
    {
        int mid=left+(right-left)/2;
        if(arr[mid]==target)
            return mid;
        else if(arr[mid] < target )
        {
            left=mid+1;
        }
        else
        {
            right=mid-1;
        }
    }

    return -1;
}


int bs_reverse(vector<int> &arr, int target, int l, int r)
{
    int left=l;
    int right=r;

    while(left<=right)
    {
        int mid=left+(right-left)/2;
        if(arr[mid]==target)
            return mid;
        else if(arr[mid] > target )
        {
            left=mid+1;
        }
        else
        {
            right=mid-1;
        }
    }

    return -1;
}

int peakEle(vector<int> &arr)
{
    int n=arr.size();
    int left=0;
    int right=n-1;
    
    while(left<=right)
    {
        int mid=left+(right-left)/2;
        int prev=mid-1<0 ? -1e8 : arr[mid-1];
        int next=mid+1>=n ? -1e8 : arr[mid+1];
        
        if(prev < arr[mid] && arr[mid] > next)
            return mid;
        else if(prev > arr[mid] )
        {
            right=mid-1;
        }
        else
        {
            left=mid+1;     //when arr[mid] < next
        }
    }
    return -1;
}

int find(vector<int> &arr, int val) 
{
    int n=arr.size();
    int left=0;
    int right=n-1;
    
    int divide=peakEle(arr);
    if(arr[divide]==val)
        return divide;
    else
    {
        int l_ans=bs(arr,val,left,divide-1);
        if(l_ans!=-1)
            return l_ans;
        int r_ans=bs_reverse(arr,val,divide+1,right);
        if(r_ans!=-1)
            return r_ans;
    }
    
    return -1;
}

int main() {
	//code
	int t;
	cin>>t;
	while(t-- > 0) {
	    int i=0;
	    int len;
	    cin>>len;
	    vector<int> arr(len);
	    while(i!=len) {
	        cin>>arr[i++];
	    }
	    int target;
	    cin>>target;
	    cout<<find(arr,target)<<endl;
	}
	return 0;
}


// 74. Search a 2D Matrix
// Integers in each row are sorted from left to right.
// The first integer of each row is greater than the last integer of the previous row.
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n=matrix.size();
        if(n==0) return false;
        int m=matrix[0].size();
        if(m==0) return false;
     
        int top_i=0;
        int down_i=n-1;
        int i=-1;
        
        while(top_i <= down_i) {        //finding the correct row by applying binary search
            int mid=top_i+(down_i-top_i)/2;
            if(target >= matrix[mid][0] && target<=matrix[mid][m-1])
            {
                i=mid;
                break;
            }
            else if(target < matrix[mid][0])
                down_i=mid-1;
            else
                top_i=mid+1;  
        }
        
        if(i==-1) return false;     //correct row not found, its false
        
        int left_j=0;
        int right_j=m-1;
        
        while(left_j<=right_j) {        //bs in the sorted row to find the element.
            int mid=left_j+(right_j-left_j)/2;
            if(matrix[i][mid]==target)
                return true;
            else if(matrix[i][mid] < target) 
                left_j=mid+1;
            else
                right_j=mid-1;
        }
        
        return false;
        
    }
};

//240. Search a 2D Matrix II
//Integers in each row are sorted in ascending from left to right.
// Integers in each column are sorted in ascending from top to bottom.

// key poiint : find a point from where u can decide that in this direction , we ll get increasing and decreasing in other
// so that u can move the left and right
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n=matrix.size();
        if(n==0) return false;
        int m=matrix[0].size();
        if(m==0) return false;
     
        int i=n-1;
        int j=0;
        
        while(i>=0 && i<n && j>=0 && j<m) {
            if(matrix[i][j]==target)
                return true;
            else if(target < matrix[i][j])
                i--;
            else
                j++;
        }
        
        return false;
    }
};


//IMPORTANT=====================================================
// https://www.youtube.com/watch?v=j3187M1P2Xg
//leetcode : 153:
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n=nums.size();
        if(n==1) return nums[0];
        
        int left=0;
        int right=n-1;
        
        while(left < right) 
        {
            int mid=left+(right-left)/2;
          
            if(nums[mid] > nums[right] ) 
            {
                left=mid+1;
            }
            else{
                right=mid;
            }
        }
        
        return nums[left];
    }
};

//leetcode : 154
class Solution {
public:
    int findMin(vector<int>& nums) 
    {
        int n=nums.size();
        if(n==1) return nums[0];
        
        int left=0;
        int right=n-1;
        int ans=+1e9;
        
        while(left <= right) 
        {
            int mid=left+(right-left)/2;
          
            if(nums[mid] > nums[right])     //mid kbhi answer nhi bn skta  as we want minimum and nums[mid] itself cannot be the answer as its greater than nums[right], throw it out of window
            {
                left=mid+1;
            }
            else if(nums[mid] < nums[right]){   //as we only nums[mid] is lesser than nums[right], so it could be the least, dont throw it out of window
                right=mid;
            }
            else    //since they are equal we can discard the last one, so that (left ,right) becomes (left,right-1) ,it wont change anything
            {
                right--;
            }

        }
        
        return nums[left];
    }
};

