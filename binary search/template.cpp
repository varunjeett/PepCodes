// https://leetcode.com/discuss/general-discussion/786126/python-powerful-ultimate-binary-search-template-solved-many-problems

// 1011. Capacity To Ship Packages Within D Days
class Solution {
public:
    // determines whether we can transport the packages within 'k' days if the boat capacity is 'w'
    bool f(int w,int d,vector<int>& arr)
    {
        int days = 1;
        int total = 0;
        for (int weight : arr)
        {
            total += weight;
            if (total > w)      // too heavy, wait for the next day
            {   
                total = weight;
                days += 1;
                if (days > d)   // cannot ship within D days
                   return false;
            }
        }
           
        return true;
    }
    
    int shipWithinDays(vector<int>& w, int d) {
        
        int sum=0,mx=0;
        for(int ele:w)
        {
            mx=max(mx,ele);
            sum+=ele;
        }
        
        int left=mx,right=sum;
        while(left < right) 
        {
            int mid=left+(right-left)/2;    //mid is the weight
            
            if(f(mid,d,w))   //finding minimum,if feasible try to find the minimum , BUT keep the current mid in the window(from (l,right) to (l,mid))
                right=mid;   
            else
                left=mid+1; //increasing capacity
        }
        
        return left;   
    }
};

// 410. Split Array Largest Sum
class Solution {
public:
    
    //mx is the mx sum possible of a group
    //group is the no of groups
    //f will return true if we can divide the array into m groups with sum of each group is less than mx
    
    bool f(long mx,vector<int>& nums, int group) 
    {
        long total=0;
        int cnt=1;  //present groups
        for(int ele:nums)
        {
            total+=ele;
            if(total > mx)
            {
                total=ele;//
                cnt++;
                if(cnt > group) //(if present groups > alloted groups)
                    return false;
            }
        }
        
        return true;
    }
    
    int splitArray(vector<int>& nums, int group) 
    {
        long sum=0,mx=0;
        for(int ele:nums)
        {
            mx=max(mx,(long)ele);
            sum+=ele;
        }
        
        long left=mx,right=sum;
        while(left < right) 
        {
            long mid=left+(right-left)/2;    //mid is the weight
            
            if(f(mid,nums,group))   //finding minimum
                right=mid;   
            else
                left=mid+1; //increasing capacity
        }
        
        return left;   
    }
};

// 875. Koko Eating Bananas
class Solution {
public:
    bool f(long speed,vector<int>& nums,int H) 
    {
        long total=0;
        for(int ele:nums)
        {
            
            float cur_hr=(ele*1.0)/(speed*1.0);
            int h=ceil(cur_hr);
            total+=h;
            if(total > H)
                return false;
        }
        return true;
    }
    
    int minEatingSpeed(vector<int>& nums, int H) {
       
        long mx=0;
        for(int ele:nums)
        {
            mx=max(mx,(long)ele);
        }
        
        long left=1,right=mx;
        while(left < right) 
        {
            long mid=left+(right-left)/2;    //mid is the weight
            
            if(f(mid,nums,H))   //finding minimum
                right=mid;   
            else
                left=mid+1; //increasing capacity
        }
        
        return left;  

    }
};


public static String find(String s1,List<String> months)
{
    String [] arr=s1.split(" ");
    int cur_day=Integer.parseInt(arr[0].substring(0,arr[0].length()-2));
    int cur_mon=months.indexOf(arr[1])+1;
    String ans=arr[2]+"-"+cur_mon+"-"+cur_day;
    return ans;
}

public static List<String> preprocessDate(List<String> arr) 
{
    // Write your code here
    if(arr.size()==0)
    {
        return new ArrayList<>();
    }

    String []mon={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    List<String> months=Arrays.asList(mon);

    List<String> ans=new ArrayList<>();
    for(String str:arr)
    {
        String ret=find(str,months);
        ans.add(ret);
    }

    return ans;
}
