#include <iostream>
#include <vector>

using namespace std;

void s012(vector<int> &arr)
{
    int i,j,k;
    i=0;j=0;k=arr.size()-1;
    while(i<(k+1))
    {
        //region of 0 to j-1 belongs to '0'
        if(arr[i]==0)
        {
            swap(arr[i],arr[j]);
            j++;
        }
        //region of k+1 to end belongs to '2'
        else if(arr[i]==2)
        {
            swap(arr[i],arr[k]);
            k--;
            //as we need to check for the swapped value , whether it is 0 ,1 ,2
            i--;
        }

        //region of j to i-1 belongs to '1'
        i++;
    }

    return;
}


void solve()
{
    vector<int> arr={0,1,2,1,1,0,1,2,1,0,0,1,1,2,2,2,2,1,0,0,0,0,1,1,1,1,1};
    s012(arr);
    for(int ele:arr)
        cout<<ele<<" ";
}

int main()
{
    solve();
}