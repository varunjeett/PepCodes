// 1043. Partition Array for Maximum Sum
class Solution {
    
    public int find(int idx,int k,int[] arr,int n,int[][]dp)
    {
        if(idx==n)
            return dp[idx][k]=0;
        
        if(dp[idx][k]!=0)
            return dp[idx][k];
        
        int ans=Integer.MIN_VALUE;

        int maxofwindow=Integer.MIN_VALUE;
        //extending the window till its size becomes k and exploring all possibility
        for(int len=0;len<k;len++)
        {
            if(idx+len<n)
            {
                // While looping, keep the max of the current window(partition) 
                // System.out.println(idx+" "+(idx+len));
                maxofwindow=Math.max(maxofwindow,arr[idx+len]);
                int ret=(maxofwindow*(len+1))+find(idx+len+1,k,arr,n,dp);
                ans=Math.max(ans,ret);
            }
            else    // For the first time, u go out of bounds, no need to extend further as it will always go out of bound
                break;
        }
        
        return dp[idx][k]=ans;
    }
    
    public int maxSumAfterPartitioning(int[] arr, int k) {
        int n=arr.length;
        int [][]dp=new int[n+1][k+1];
        return find(0,k,arr,n,dp);
    }
}

// Virtually creating k subset of equal sum by dfs
// 698. Partition to K Equal Sum Subsets
class Solution {
     
    //sudoku type backtracking problem
    public boolean canPartitionKSubsets(int[] nums, int k) {
        
        int sum=0;
        for(int ele:nums)
            sum+=ele;
        
        if((sum%k)!=0)  //total sum cannot be divided equally into k subsets
            return false;
        
        int target=(sum/k);   //each subset should have only target value
        
        Arrays.sort(nums);
        
        //biggest element of array is greeater than target value,never possible
        if(nums[nums.length-1] > target)
            return false;
        
        boolean []vis = new boolean[nums.length];
        
        return canPart(nums.length-1,target,k,nums,vis,target);
    }
    
    public boolean canPart(int idx,int target,int rem_k,int []nums,boolean []vis,int otarget) {
        
        //remaining subset to be created 
        if(rem_k==0)
            return true;
        
        //current subset is completed,find for the next one, for the next subset, consider all values, except for the visited ones,because they are already utilised
        if(target==0)
            return canPart(nums.length-1,otarget,(rem_k-1),nums,vis,otarget);
        
        //required value not found
        if(idx < 0)
            return false;
        
        boolean res=false;
        for(int i=idx; i>=0 && !res ;i--)
        {
            if(!vis[i] && target-nums[i] >= 0)
            {
                //passing i from here because, all values before i are already tried, so look for 
                vis[i]=true;
                res=res || (canPart(i-1,target-nums[i],rem_k,nums,vis,otarget));
                vis[i]=false;
            }
        }
        return res;
    }
}


// 416. Partition Equal Subset Sum
// Given a non-empty array containing only positive integers, 
// find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

//Convert it to target type question , find a subset with sum equal to (total sum / 2)
class Solution {
    public boolean canPartition(int[] nums) {
        int sum=0;
        for(int ele:nums)
            sum+=ele;
        
        if((sum%2)!=0)  //total sum odd, cannot be divided equally
            return false;
        
        int target=sum/2;
        
        // dp[][]=1  implies possible
        // dp[][]=-1 implies not possible
        // initially whole dp is 0 
        int [][]dp=new int[nums.length+1][target+1];
        
        int ans=find(0,target,nums,dp);
        return (ans==1) ? true:false;
    }
    
    int find(int idx,int target,int[]nums,int[][]dp)
    {
        if(idx==nums.length || target==0)
        {
            if(target==0)
                return dp[idx][target]=1;
            return dp[idx][target]=-1;   
        }
        
        if(dp[idx][target]!=0)
            return dp[idx][target];
        
        boolean res=false;
        //yes ki call
        
        if(target-nums[idx]>=0)
        {
            res=res || ( (find(idx+1,target-nums[idx],nums,dp)==1) ? true:false);
        }
        
        //no ki call
        res=res || ( (find(idx+1,target,nums,dp)==1) ? true:false);
        
        return dp[idx][target]= (res==true) ? 1 : -1;
    }
}