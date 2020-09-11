// 1356. Sort Integers by The Number of 1 Bits

// Count the bits by losing one set bit at a time..
class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        int n=arr.size();
        if(n<=1)
            return arr;
        
        sort(arr.begin(),arr.end(),[](const int &t,const int &o) -> bool {
            
            int t_b=0;
            int num=t;
            while(num > 0)
            {
                // num=(num&((!num)+1)) will give overflow
                num=(num&(num-1));
                t_b++;
            }
            

            num=o;
            int o_b=0;           
            while(num > 0)
            {
                // num=(num&((!num)+1)) will give overflow
                num=(num&(num-1));
                o_b++;
            }
    
            
            if(t_b==o_b)
                return t < o;
            return t_b < o_b; 

        });
        
        return arr;
    }
};

