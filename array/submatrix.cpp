// 1074. Number of Submatrices That Sum to Target
class Solution
{
public:
    int subArrK(vector<int> &arr, int target)
    {
        if (arr.size() == 0)
            return 0;

        int count = 0;
        unordered_map<int, int> map;
        int rsum = 0;

        for (int i = 0; i < arr.size(); i++)
        {
            rsum += arr[i];

            //current subarray equal to target
            if (rsum == target)
                count++;

            int tar = rsum - target;
            //finding counterpartand exploring other possibility
            if (map.find(tar) != map.end())
            {
                count += map[tar];
            }

            //insert in map
            map[rsum]++;
        }

        return count;
    }
    int numSubmatrixSumTarget(vector<vector<int>> &matrix, int target)
    {

        // On a 2-D array, to explore all the submatrices, we need to loop like

        // a b c d
        // d e f g
        // h i j k

        // we keep a 'l' pointer as the left boundary for the submatrix and 'r' as right boundary
        // for every l(from 0 to m), the right pointer goes from (l to m)

        int n = matrix.size();
        int m = matrix[0].size();

        int ans = 0;

        for (int l = 0; l < m; l++)
        {
            vector<int> temp(n, 0);

            for (int r = l; r < m; r++)
            {
                for (int k = 0; k < n; k++)
                {
                    temp[k] += matrix[k][r];
                }

                ans += subArrK(temp, target);
            }
        }

        return ans;
    }
};

// 1504. Count Submatrices With All Ones
// N*N*N complexity
class Solution
{
public:
    int numSubmat(vector<vector<int>> &arr)
    {

        int n = arr.size();
        int m = arr[0].size();

        vector<vector<int>> arr2(n, vector<int>(m, 0));

        //for each one in the given matrix we calculate the no of 1-D subarray consisting of all 1 starting from that element

        for (int i = 0; i < n; i++)
        {
            // for     [1,1,0,1,1,1,0,1,1]
            // we fill [2,1,0,3,2,1,0,2,1]

            int len = 0; //1-D subarray from starting from here
            for (int j = m - 1; j >= 0; j--)
            {
                if (arr[i][j] == 1)
                {
                    //if arr[i][j+1] would be zero, then len=0, so we increment len and store (len+1) at arr2.
                    len++;
                    arr2[i][j] = len;
                }
                else
                {
                    len = 0;
                    arr2[i][j] = len;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (arr2[i][j] != 0)
                {
                    int bottleneck = INT_MAX;
                    //we keep the col fixed at for all the down rows calculate the submatrices possible
                    for (int k = i; k < n; k++)
                    {
                        //row fixed and traversing downward columns
                        bottleneck = min(bottleneck, arr2[k][j]);
                        ans += bottleneck;
                    }
                }
            }
        }

        return ans;
    }
};

class Solution
{
public:
    int countSquares(vector<vector<int>> &arr)
    {
        int n = arr.size();
        int m = arr[0].size();

        vector<vector<int>> arr2(n, vector<int>(m, 0));
        //for each one in the given matrix we calculate the no of 1-D subarray consisting of all 1 starting from that element

        for (int i = 0; i < n; i++)
        {
            // for     [1,1,0,1,1,1,0,1,1]
            // we fill [2,1,0,3,2,1,0,2,1]

            int len = 0; //1-D subarray from starting from here
            for (int j = m - 1; j >= 0; j--)
            {
                if (arr[i][j] == 1)
                {
                    //if arr[i][j+1] would be zero, then len=0, so we increment len and store (len+1) at arr2.
                    len++;
                    arr2[i][j] = len;
                }
                else
                {
                    len = 0;
                    arr2[i][j] = len;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                //we keep the col fixed at for all the down rows calculate the submatrices possible
                if (arr2[i][j] != 0)
                {
                    int bottleneck = arr2[i][j];
                    ans += 1; //square of side 1;

                    //start finding for sqaure of greater side starting from 2
                    int side = 2;
                    while (side <= bottleneck)
                    {
                        //for side 2, we go one row down, for side 3 , 2 row down, therefore its i+(side-1);
                        if ((i + (side - 1) < n) && arr2[i + (side - 1)][j] >= side)
                        {
                            //3 2 1 0
                            //2 1 0 0
                            //4 3 2 1
                            //In the above case bottle neck needs to be updated
                            bottleneck = min(bottleneck, arr2[i + (side - 1)][j]);
                            ans += 1;//square of that particular side to be included
                            side++;
                        }
                        else
                            break;
                    }
                }
            }
        }

        return ans;
    }
};

// Think about how to calculate the value for one cell fast??
// 1314. Matrix Block Sum
class Solution {
public:
    // Use the concept of cumulative sum array.
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& arr, int k) {
        int n=arr.size();
        int m=arr[0].size();
        
        vector<vector<int>> arr2(n,vector<int>(m,0));
        //for each row in the given matrix we calculate the prefix sum array
        
        for(int i=0;i<n;i++)
        {  
            int csum=0;//1-D subarray from starting from here
            for(int j=0;j<m;j++)
            {
                csum+=arr[i][j];
                arr2[i][j]=csum;
            }
        }
        
        
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                int left=max(0,j-k);
                int right=min(m-1,j+k);
                int up=max(0,i-k);
                int down=min(n-1,i+k);
                
                int totalsum=0;
                for(int k=up;k<=down;k++)
                {
                    //prefix sum condition for querying
                    if(left==0)
                        totalsum+=arr2[k][right];
                    else
                        totalsum+=(arr2[k][right]-arr2[k][left-1]);
                }
                
                arr[i][j]=totalsum;
            }
        }
        
        return arr;
    }
};