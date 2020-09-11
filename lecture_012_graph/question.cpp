//leetcode 542.==================================================
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& arr) {

        int n=arr.size();
        int m=arr[0].size();
        
        queue<int> q;
        vector<vector<bool>>vis(n,vector<bool>(m,false));
        
        for(int i=0;i<n; i++) {
            for(int j=0; j<m; j++) {
                if(arr[i][j]==0) {
                    q.push(i*m+j);      //pushing all zeroes 
                    vis[i][j]=true;
                }
            }
        }
        
        int level=0;
        vector<int> dir={-1,0,1,0,-1};
        
        while(q.size()!=0) {
            int sz=q.size();
            while(sz-- > 0) {
                
                int ele=q.front();
                q.pop();
                int r=ele/m;
                int c=ele%m;
                
                arr[r][c]=level;    //consider it as a virtual zero ,as a path for other one.===
                for(int d=0; d<dir.size()-1;d++){
                    int x=r+dir[d];
                    int y=c+dir[d+1];
                    
                    if(x>=0 && y>=0 && x<n && y<m && arr[x][y]==1 && !vis[x][y]) {
                        q.push(x*m+y);
                        vis[x][y]=true;
                    }
                    
                }   
            }
            level++;
            
        }
        
        return arr;
        
    }
};