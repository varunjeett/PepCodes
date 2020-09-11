#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partition(int st,int ed,vector<int> &arr,int pivot)
{
    int i=st-1;
    int j=st;
    while (j <= ed)
    {
        if(arr[j] <= pivot)
        {
            ++i;
            swap(arr[i],arr[j]);
        }
        j++;
    }
    return i;
}
//kth smallest
int quickSelect(int st,int ed,int k,vector<int> &arr)
{
    if(st > ed)
    {
        return -1;
    }

    int pivot=arr[ed]; 
    int pos=partition(st,ed,arr,pivot);

    if(pos+1 == k)
    {
        return arr[pos];
    }

    else if(pos+1 < k)
    {
        return quickSelect(pos+1,ed,k,arr);
    }
    else
    {
        return quickSelect(st,pos-1,k,arr);
    }
}

void solve()
{
    vector<int> arr={2,5,10,12,8,9,13,20,2,5};
    int k=12;
    sort(arr.begin(),arr.end());
    
    for(int ele:arr)
        cout<<ele<<" ";

    cout <<endl<< quickSelect(0,arr.size()-1,k,arr)<<endl;

}

int main()
{
    solve();
}